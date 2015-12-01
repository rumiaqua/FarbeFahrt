#include "Camera.h"
#include <memory>
#include "Utility/Math.h"
#include "Utility/Mouse.h"
# include "Utility/Vector3.h"
# include "Utility/MemoryCast.h"
#include "Utility/MemoryCast.h"
#include "Utility/String.h"
#include "Utility/Debug.h"
# include "Utility/StoryManager/StoryManager.h"

#include "Ray.h"

namespace
{
	// 何秒かけて遷移するか
	static const float SECOND = 1.0f;
	using Func = std::function<void()>;
}

Camera::Camera(IWorld& world) :
	BaseActor(world, "Camera", Vector3::Zero(), Matrix::identity(), nullptr)
	, m_onCompleted(false)
{
	SetCameraNearFar(1.0f, 12000.0f);
	SetCursorPos(nScreenCenterX, nScreenCenterY);

	m_cameraMatrix.targetPos = { -65.0f, 140.0f, -150.0f };
	m_cameraMatrix.currentPos = m_cameraMatrix.targetPos;

	m_cameraMatrix.targetRot = { -65.0f, 0.0f, 0.0f };
	m_cameraMatrix.currentRot = m_cameraMatrix.targetRot;

	m_cameraState.chaseFlag = ChaseFlag::Void;
	m_cameraState.cameraMode = CameraMode::Default;

	m_t = 1.0f;
}
void Camera::onUpdate()
{
	if (m_actor.expired())
	{
		actorSet("Player");
	}

	Debug::Println("%f", m_t);
	Debug::Println(String::Create("CameraMode:", (int)m_cameraState.cameraMode));
	Debug::Println(String::Create("ChageFlag :", (int)m_cameraState.chaseFlag));

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
		m_world->addActor(ActorTag::Collider, std::make_shared<Ray>(*m_world, begin, end));

		Debug::Println("{%f,%f,%f}", begin.x, begin.y, begin.z);
	}
}

void Camera::chaseCamera()
{
	if (m_actor.expired())
	{
		return;
	}
	Actor actor = m_actor.lock();
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	////移行できるカメラ
	//toBookCamera();
	//toFixedCamera();
}

void Camera::fadeInCamera()
{
	if (m_actor.expired())
	{
		return;
	}
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
	m_cameraMatrix.targetPos = { -145.0f / 2, 140.0f, -150.0f };
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = { -145.0f / 2, 0.0f, 0.0f };
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeInFixedCamera()
{
	if (m_actor.expired())
	{
		return;
	}
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
	if (m_actor.expired())
	{
		return;
	}
	Actor actor = m_actor.lock();
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	////移行できるカメラ
	//toBookCamera();
	//toPlayerCamera();
}

void Camera::defaultCamera()
{
	if (m_actor.expired())
	{
		return;
	}
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
	//else
	//{
	//	if (m_t >= 1)
	//	{
	//		//移行できるカメラ
	//		toPlayerCamera();
	//		toFixedCamera();
	//	}
	//}
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

	funcs.at(m_cameraState.cameraMode)();

	m_t += 1 / (60.0f * SECOND);
	m_t = m_t > 1.0f ? 1.0f : m_t;

	if (m_onCompleted && m_t == 1.0f)
	{
		m_onCompleted = false;
		StoryManager::set(BitFlag::GOAL);
	}

	getPosition() = Vector3::Lerp(m_cameraMatrix.currentPos, m_cameraMatrix.targetPos, static_cast<float>(Math::Sin(Math::HALF_PI * m_t)));
	Vector3 focus = Vector3::Lerp(m_cameraMatrix.currentRot, m_cameraMatrix.targetRot, static_cast<float>(Math::Sin(Math::HALF_PI * m_t)));

	SetCameraPositionAndTarget_UpVecY(getPosition(), focus);
}

void Camera::toBookCamera()
{
	if (m_cameraState.cameraMode == CameraMode::LockAt || m_cameraState.cameraMode == CameraMode::Chase)
	{
		m_t = 0;
		m_cameraState.cameraMode = CameraMode::FadeOut;
	}
}

void Camera::toPlayerCamera()
{
	if (m_cameraState.cameraMode == CameraMode::LockAt || m_cameraState.cameraMode == CameraMode::Default)
	{
		m_cameraState.cameraMode = CameraMode::FadeIn;
	}
}

void Camera::toFixedCamera()
{
	if (m_cameraState.cameraMode == CameraMode::Chase || m_cameraState.cameraMode == CameraMode::Default)
	{
		m_cameraState.cameraMode = CameraMode::FadeInFixed;
	}
}

void Camera::actorSet(const std::string& actorName)
{
	m_actor = m_world->findActor(actorName);
}

void Camera::onMessage(const std::string& message, void* parameter)
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
		m_onCompleted = true;
	}

	if (message == "complete")
	{
		m_onCompleted = true;
	}

	if (m_t >= 1 )
	{
		if (message == "toBookCamera")		toBookCamera();
		if (message == "toPlayerCamera")	toPlayerCamera();
		if (message == "toFixedCamera")		toFixedCamera();
	}

	BaseActor::onMessage(message, parameter);
}