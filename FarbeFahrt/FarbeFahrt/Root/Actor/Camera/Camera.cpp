#include "Camera.h"
#include <memory>
#include "Utility/Math.h"
#include "Utility/Mouse.h"
#include "Ray.h"

# include "Utility/Vector3.h"
# include "Utility/MemoryCast.h"
#include "Utility/MemoryCast.h"
#include "Utility/String.h"

#include "Utility/Debug.h"

namespace
{
	// 何秒かけて遷移するか
	static const float SECOND = 1.0f;
	using Func = std::function<void()>;
}

Camera::Camera(IWorld& world) :
BaseActor(world, "Camera", Vector3::Zero(), Matrix::identity(), nullptr)
{
	SetCameraNearFar(1.0f, 12000.0f);
	SetCursorPos(nScreenCenterX, nScreenCenterY);

	m_cameraMatrix.targetPos = { 0.0f, 20.0f, -30.0f };
	m_cameraMatrix.currentPos = m_cameraMatrix.targetPos;

	m_cameraMatrix.targetRot = { 0.0f, 15.0f, 0.0f };
	m_cameraMatrix.currentRot = m_cameraMatrix.targetRot;

	m_cameraState.chaseFlag = ChaseFlag::Void;
	m_cameraState.cameraMode = CameraMode::Init;
}
void Camera::onUpdate()
{
	if (m_actor.expired())
	{
		actorSet("Player");
	}

	cameraInput();
	cameraSet();

	BaseActor::onUpdate();
}

void Camera::onDraw(Renderer& render)const
{
	BaseActor::onDraw(render);
}

void Camera::cameraInput()
{
	if (Mouse::IsPressed(MOUSE_INPUT_LEFT))
	{
		Vector3 begin = Mouse::ScreenPointToWorld(0.0f);
		Vector3 end = Mouse::ScreenPointToWorld(1.0f);
		m_world->addActor(ActorTag::Collider,std::make_shared<Ray>(*m_world, begin, end));

		Debug::Println("{%f,%f,%f}", begin.x,begin.y,begin.z);
	}
}

void Camera::chaseCamera()
{
	Actor actor = m_actor.lock();
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toFixedCamera();
}

void Camera::fadeInCamera()
{
	Actor actor = m_actor.lock();
	m_cameraMatrix.currentPos = getPosition();
	m_t = 0;
	m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
	m_cameraState.chaseFlag = ChaseFlag::Move;
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeOutCamera()
{
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = { 0.0f, 140.0f, -150.0f };
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = { 0.0f, 0.0f, 0.0f };
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeInFixedCamera()
{
	Actor actor = m_actor.lock();
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = getPosition();
	m_t = 0;
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
	m_cameraState.chaseFlag = ChaseFlag::Stay;
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::lockCamera()
{
	Actor actor = m_actor.lock();
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toPlayerCamera();
}

void Camera::defaultCamera()
{
	Actor actor = m_actor.lock();
	if (m_cameraState.chaseFlag == ChaseFlag::Move)
	{
		m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
		m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
		if (m_t >= 1)
		{
			m_cameraState.chaseFlag = ChaseFlag::Void;
			m_cameraState.cameraMode = CameraMode::Chase;
		}
	}
	else if (m_cameraState.chaseFlag == ChaseFlag::Stay)
	{
		m_cameraMatrix.targetPos = getPosition();
		m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
		if (m_t >= 1)
		{
			m_cameraState.chaseFlag = ChaseFlag::Void;
			m_cameraState.cameraMode = CameraMode::LockAt;
		}
	}
	else
	{
		if (m_t >= 1)
		{
		//移行できるカメラ
		toPlayerCamera();
		toFixedCamera();
	}
}
}

void Camera::initCamera()
{
	Actor actor = m_actor.lock();
	m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
	getPosition() = m_cameraMatrix.targetPos;

	SetCameraPositionAndTarget_UpVecY(getPosition(), m_cameraMatrix.targetRot);

	m_cameraState.cameraMode = CameraMode::Chase;
}

void Camera::cameraSet()
{
	static std::unordered_map<CameraMode, Func> funcs;
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Chase, [this]() { this->chaseCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeIn, [this]() { this->fadeInCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeOut, [this]() { this->fadeOutCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Default, [this]() { this->defaultCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeInFixed, [this]() { this->fadeInFixedCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::LockAt, [this]() { this->lockCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Init, [this]() { this->initCamera(); }));

	if (m_actor.expired())
	{
		return;
	}
	funcs.at(m_cameraState.cameraMode)();

	m_t += 1 / (60.0f * SECOND);
	m_t = m_t > 1.0f ? 1.0f : m_t;
	getPosition() = Vector3::Lerp(m_cameraMatrix.currentPos, m_cameraMatrix.targetPos, static_cast<float>(Math::Sin(Math::HALF_PI * m_t)));
	Vector3 focus = Vector3::Lerp(m_cameraMatrix.currentRot, m_cameraMatrix.targetRot, static_cast<float>(Math::Sin(Math::HALF_PI * m_t)));

	SetCameraPositionAndTarget_UpVecY(getPosition(), focus);
}

//キー：Zで本視点
void Camera::toBookCamera()
{
	if (Input::IsClicked(KEY_INPUT_Z))
	{
		m_t = 0;
		m_cameraState.cameraMode = CameraMode::FadeOut;
	}
}

//キー：Xでプレイヤー視点
void Camera::toPlayerCamera()
{
	if (Input::IsClicked(KEY_INPUT_X))
	{
		m_cameraState.cameraMode = CameraMode::FadeIn;
	}
}

//キー：Cでカメラ固定回転
void Camera::toFixedCamera()
{
	if (Input::IsClicked(KEY_INPUT_C))
	{
		m_cameraState.cameraMode = CameraMode::FadeInFixed;
	}
}

void Camera::actorSet(const std::string& actorName)
{
	m_actor = m_world->findActor(actorName);
}

void Camera::onMessage(const String& message, void* parameter)
{
	if (message == "actorSet")
	{
		actorSet(*(std::string*)parameter);
		m_cameraState.cameraMode = CameraMode::FadeIn;
	}
	//責任者　なりたん
	if (message == "nextStage")
	{
		m_t = 0;
		m_cameraState.cameraMode = CameraMode::FadeOut;
	}
	BaseActor::onMessage(message, parameter);
}