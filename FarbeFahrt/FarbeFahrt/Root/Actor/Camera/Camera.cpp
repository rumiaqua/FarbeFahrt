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
#include "Collision/Sphere.h"

namespace
{
	// ‰½•b‚©‚¯‚Ä‘JˆÚ‚·‚é‚©
	static const float SECOND = 1.0f;
	using Func = std::function<void(Camera* const)>;
	Vector3 outPos = { -62.5f, 250.0f, -260.0f };
	Vector3 outRot = { -62.5f, 0.0f, 0.0f };
	Vector3 accessPos = { 0.0f, 15.0f, -25.0f };
	Vector3 accessRot = { 0.0f,15.0f,0.0f };
}

Camera::Camera(IWorld& world) :
	BaseActor(world, "Camera", Vector3::Zero(), Matrix::identity(), nullptr)
	, m_onCompleted(false)
	, m_actor()
{
	SetCameraNearFar(1.0f, 12000.0f);
	// SetCursorPos(nScreenCenterX, nScreenCenterY);

	m_cameraMatrix.targetPos = outPos;
	m_cameraMatrix.currentPos = m_cameraMatrix.targetPos;

	m_cameraMatrix.targetRot = outRot;
	m_cameraMatrix.currentRot = m_cameraMatrix.targetRot;

	m_cameraState.chaseFlag = ChaseFlag::Void;
	m_cameraState.cameraMode = CameraMode::Default;

	m_progress = 1.0f;
	m_lockPos = none;
	actorSet("Player");
	m_actorRadius = 0.0f;
}
void Camera::onUpdate()
{
	if (!m_actor.expired())
	{
		m_lockPos = m_actor.lock()->getPosition();
		m_actorRadius = static_cast<Sphere*>(m_actor.lock()->getShape())->radius;
	}

	//Debug::Println("%f", m_progress);
	//Debug::Println(String::Create("CameraMode:", (int)m_cameraState.cameraMode));
	//Debug::Println(String::Create("ChageFlag :", (int)m_cameraState.chaseFlag));

	if (m_progress >= 1)
	{
		cameraInput();
	}
	cameraSet();



	BaseActor::onUpdate();
}

void Camera::onDraw(Renderer& renderer)const
{
	BaseActor::onDraw(renderer);
}

void Camera::cameraInput()
{
	if (Mouse::IsClicked(MOUSE_INPUT_LEFT)/* && m_cameraState.cameraMode == CameraMode::Default*/)
	{
		Vector3 begin = Mouse::ScreenPointToWorld(0.0f);
		Vector3 end = Mouse::ScreenPointToWorld(1.0f);
		m_world->addActor(ActorTag::Collider, std::make_shared<Ray>(*m_world, begin, end));
	}

	if (Mouse::ScrollValue() > 0)
	{
		toPlayerCamera();
	}
	else if (Mouse::ScrollValue() < 0)
	{
		toBookCamera();
	}
}

void Camera::chaseCamera()
{
	if (m_actor.expired() && !m_lockPos)
	{
		return;
	}
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = m_lockPos.ref() + accessCorrection(accessPos);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_lockPos.ref() + accessRot;
}

void Camera::fadeInCamera()
{
	if (m_actor.expired() && !m_lockPos)
	{
		return;
	}
	m_cameraMatrix.currentPos = getPosition();
	m_progress = 0;
	m_cameraMatrix.targetPos = m_lockPos.ref() + accessCorrection(accessPos);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_lockPos.ref() + accessRot;
	m_cameraState.chaseFlag = ChaseFlag::Move;
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeOutCamera()
{
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = outPos;
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = outRot;
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeInFixedCamera()
{
	if (m_actor.expired() && !m_lockPos)
	{
		return;
	}
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = getPosition();
	m_progress = 0;
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_lockPos.ref() + accessRot;
	m_cameraState.chaseFlag = ChaseFlag::Stay;
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::lockCamera()
{
	if (m_actor.expired() && !m_lockPos)
	{
		return;
	}
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = m_lockPos.ref() + accessRot;
}

void Camera::defaultCamera()
{
	if (m_actor.expired() && !m_lockPos)
	{
		return;
	}
	if (m_cameraState.chaseFlag == ChaseFlag::Move)
	{
		m_cameraMatrix.targetPos = m_lockPos.ref() + accessCorrection(accessPos);
		m_cameraMatrix.targetRot = m_lockPos.ref() + accessRot;
		if (m_progress >= 1)
		{
			m_cameraState.chaseFlag = ChaseFlag::Void;
			m_cameraState.cameraMode = CameraMode::Chase;
		}
	}
	else if (m_cameraState.chaseFlag == ChaseFlag::Stay)
	{
		m_cameraMatrix.targetPos = getPosition();
		m_cameraMatrix.targetRot = m_lockPos.ref() + accessRot;
		if (m_progress >= 1)
		{
			m_cameraState.chaseFlag = ChaseFlag::Void;
			m_cameraState.cameraMode = CameraMode::LockAt;
		}
	}
}

void Camera::cameraSet()
{
	static const std::unordered_map<CameraMode, Func> funcs
	{
		{ CameraMode::Chase, [](Camera* const camera) { camera->chaseCamera(); } },
		{ CameraMode::FadeIn, [](Camera* const camera) { camera->fadeInCamera(); } },
		{ CameraMode::FadeOut, [](Camera* const camera) { camera->fadeOutCamera(); } },
		{ CameraMode::Default, [](Camera* const camera) { camera->defaultCamera(); } },
		{ CameraMode::FadeInFixed, [](Camera* const camera) { camera->fadeInFixedCamera(); } },
		{ CameraMode::LockAt, [](Camera* const camera) { camera->lockCamera(); } },
	};

	funcs.at(m_cameraState.cameraMode)(this);

	m_progress += 1 / (60.0f * SECOND);
	m_progress = m_progress > 1.0f ? 1.0f : m_progress;

	if (m_onCompleted && m_progress == 1.0f)
	{
		m_onCompleted = false;
		StoryManager::set(BitFlag::GOAL);
	}

	getPosition() = Vector3::Lerp(m_cameraMatrix.currentPos, m_cameraMatrix.targetPos, static_cast<float>(Math::Sin(Math::HALF_PI * m_progress)));
	Vector3 focus = Vector3::Lerp(m_cameraMatrix.currentRot, m_cameraMatrix.targetRot, static_cast<float>(Math::Sin(Math::HALF_PI * m_progress)));

	SetCameraPositionAndTarget_UpVecY(getPosition(), focus);
}

void Camera::toBookCamera()
{
	if (m_cameraState.cameraMode == CameraMode::LockAt || m_cameraState.cameraMode == CameraMode::Chase)
	{
		m_progress = 0;
		m_cameraState.cameraMode = CameraMode::FadeOut;
		actorSet("Player");
		if (m_actor.expired())
		{
			return;
		}
		bool isKill = false;
		m_actor.lock()->sendMessage("StopControl", &isKill);
	}
}

void Camera::toPlayerCamera()
{
	if (m_cameraState.cameraMode == CameraMode::LockAt || m_cameraState.cameraMode == CameraMode::Default)
	{
		m_cameraState.cameraMode = CameraMode::FadeIn;
		actorSet("Player");
		if (m_actor.expired())
		{
			return;
		}
		m_actor.lock()->sendMessage("StartControl", nullptr);
	}
}

void Camera::toFixedCamera()
{
	if (m_cameraState.cameraMode == CameraMode::Chase || m_cameraState.cameraMode == CameraMode::Default)
	{
		m_cameraState.cameraMode = CameraMode::FadeInFixed;
	}
}

Vector3 Camera::accessCorrection(Vector3 pos)
{
	return{ pos.x, pos.y + m_actorRadius, pos.z - m_actorRadius * 2 };
}

void Camera::actorSet(const std::string& actorName)
{
	m_actor = m_world->findActor(actorName);
}
void Camera::actorSet(const Vector3& position)
{
	m_actor.reset();
	m_lockPos = position;
	m_cameraState.cameraMode = CameraMode::FadeIn;
}

void Camera::onMessage(const std::string& message, void* parameter)
{
	if (message == "actorSet")
	{
		actorSet(*(Vector3*)parameter);
	}
	//Ó”CŽÒ@‚È‚è‚½‚ñ
	if (message == "nextStage")
	{
		m_progress = 0;
		m_cameraState.cameraMode = CameraMode::FadeOut;
		m_onCompleted = true;
	}

	if (message == "complete")
	{
		m_onCompleted = true;
	}

	if (m_progress >= 1)
	{
		if (message == "toBookCamera")		toBookCamera();
		if (message == "toPlayerCamera")	toPlayerCamera();
		if (message == "toFixedCamera")		toFixedCamera();
	}

	if (message == "progress")
	{
		*(float*)parameter = m_progress;
	}

	BaseActor::onMessage(message, parameter);
}