#include "Camera.h"
#include "Actor/Enemy.h"
#include <memory>
#include "Utility/Math.h"

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
BaseActor(world, "Camera", Vector3::Zero(), Matrix::identity())
{
	SetCameraNearFar(1.0f, 12000.0f);
	SetCursorPos(nScreenCenterX, nScreenCenterY);

	m_cameraMatrix.targetPos = { 0.0f, 20.0f, -30.0f };
	m_cameraMatrix.currentPos = m_cameraMatrix.targetPos;

	m_cameraMatrix.targetRot = { 0.0f, 15.0f, 0.0f };
	m_cameraMatrix.currentRot = m_cameraMatrix.targetRot;

	m_cameraState.chaseFlag = ChaseFlag::Void;
	m_cameraState.cameraMode = CameraMode::Init;

	m_actor = nullptr;
}
void Camera::onUpdate()
{
	playerCheck();
	if (m_actor == nullptr)return;

	cameraSet();
}

void Camera::onDraw(Renderer& render)const
{

}

void Camera::chaseCamera()
{
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = m_actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toFixCamera();
}

void Camera::fadeInCamera()
{
	m_cameraMatrix.currentPos = getPosition();
	m_t = 0;
	m_cameraMatrix.targetPos = m_actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
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

void Camera::fadeInFixCamera()
{
	actorCheck(m_actor->getName().toNarrow());
	if (m_actor == nullptr)return;

	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = getPosition();
	m_t = 0;
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
	m_cameraState.chaseFlag = ChaseFlag::Stay;
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::lockCamera()
{
	actorCheck(m_actor->getName().toNarrow());
	if (m_actor == nullptr)return;

	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toPlayerCamera();
}

void Camera::defaultCamera()
{
	if (m_cameraState.chaseFlag == ChaseFlag::Move)
	{
		m_cameraMatrix.targetPos = m_actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
		m_cameraMatrix.targetRot = m_actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
		if (m_t >= 1)
		{
			m_cameraState.chaseFlag = ChaseFlag::Void;
			m_cameraState.cameraMode = CameraMode::Chase;
		}
	}
	else if (m_cameraState.chaseFlag == ChaseFlag::Stay)
	{
		m_cameraMatrix.targetPos = getPosition();
		m_cameraMatrix.targetRot = m_actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
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
		toFixCamera();
	}
}
}

void Camera::initCamera()
{
	m_cameraMatrix.targetPos = m_actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	m_cameraMatrix.targetRot = m_actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
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
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeInFix, [this]() { this->fadeInFixCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::LockAt, [this]() { this->lockCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Init, [this]() { this->initCamera(); }));

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
void Camera::toFixCamera()
{
	if (Input::IsClicked(KEY_INPUT_C))
	{
		m_cameraState.cameraMode = CameraMode::FadeInFix;
	}
}

void Camera::playerCheck()
{
	actorCheck("Player");
}

void Camera::actorCheck(const std::string actorName)
{
	m_actor = m_world->findActor(actorName);
}