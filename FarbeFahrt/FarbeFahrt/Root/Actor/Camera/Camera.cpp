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
	// 何秒かけて遷移するか
	static const float SECOND = 1.0f;
	using Func = std::function<void(Camera* const)>;
}

Camera::Camera(IWorld& world) :
	BaseActor(world, "Camera", Vector3::Zero(), Matrix::identity(), nullptr)
	, m_onCompleted(false)
	, m_actor()
{
	SetCameraNearFar(1.0f, 12000.0f);
	SetCursorPos(nScreenCenterX, nScreenCenterY);

	m_cameraMatrix.targetPos = { -62.5f, 250.0f, -260.0f };
	m_cameraMatrix.currentPos = m_cameraMatrix.targetPos;

	m_cameraMatrix.targetRot = { -62.5f, 0.0f, 0.0f };
	m_cameraMatrix.currentRot = m_cameraMatrix.targetRot;

	m_cameraState.chaseFlag = ChaseFlag::Void;
	m_cameraState.cameraMode = CameraMode::Default;

	m_progress = 1.0f;
}
void Camera::onUpdate()
{
	if (m_actor.expired())
	{
		actorSet("Player");
	}

	Debug::Println("%f", m_progress);
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
	if (Mouse::IsClicked(MOUSE_INPUT_LEFT))
	{
		Vector3 begin = Mouse::ScreenPointToWorld(0.0f);
		Vector3 end = Mouse::ScreenPointToWorld(1.0f);
		m_world->addActor(ActorTag::Collider, std::make_shared<Ray>(*m_world, begin, end));
	}

	if (m_progress >= 1)
	{
		if (Mouse::ScrollValue() > 0)
		{
			toPlayerCamera();
		}
		else if(Mouse::ScrollValue() < 0)
		{
			toBookCamera();
		}
	}
}

void Camera::chaseCamera()
{
	if (m_actor.expired())
	{
		return;
	}
	Actor actor = m_actor.lock();
	float actorRadius = static_cast<Sphere*>(actor->getShape())->radius;
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 15.0f + actorRadius, -25.0f - actorRadius * 2);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 10.0f, 0.0f);
}

void Camera::fadeInCamera()
{
	if (m_actor.expired())
	{
		return;
	}
	Actor actor = m_actor.lock();
	float actorRadius = static_cast<Sphere*>(actor->getShape())->radius;
	m_cameraMatrix.currentPos = getPosition();
	m_progress = 0;
	m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 15.0f + actorRadius, -25.0f - actorRadius  * 2);
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 10.0f, 0.0f);
	m_cameraState.chaseFlag = ChaseFlag::Move;
	m_cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeOutCamera()
{
	m_cameraMatrix.currentPos = getPosition();
	m_cameraMatrix.targetPos = { -63.0f, 250.0f, -260.0f };
	m_cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	m_cameraMatrix.targetRot = { -63.0f, 0.0f, 0.0f };
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
	m_progress = 0;
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
		float actorRadius = static_cast<Sphere*>(actor->getShape())->radius;
		m_cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 15.0f + actorRadius, -25.0f - actorRadius * 2);
		m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 10.0f, 0.0f);
		if (m_progress >= 1)
		{
			m_cameraState.chaseFlag = ChaseFlag::Void;
			m_cameraState.cameraMode = CameraMode::Chase;
		}
	}
	else if (m_cameraState.chaseFlag == ChaseFlag::Stay)
	{
		m_cameraMatrix.targetPos = getPosition();
		m_cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 10.0f, 0.0f);
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
		{ CameraMode::Chase, [] (Camera* const camera) { camera->chaseCamera(); } },
		{ CameraMode::FadeIn, [] (Camera* const camera) { camera->fadeInCamera(); } },
		{ CameraMode::FadeOut, [] (Camera* const camera) { camera->fadeOutCamera(); } },
		{ CameraMode::Default, [] (Camera* const camera) { camera->defaultCamera(); } },
		{ CameraMode::FadeInFixed, [] (Camera* const camera) { camera->fadeInFixedCamera(); } },
		{ CameraMode::LockAt, [] (Camera* const camera) { camera->lockCamera(); } },
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
		m_actor.lock()->sendMessage("StopControl",(bool*)false);
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

void Camera::actorSet(const std::string& actorName)
{
	m_actor = m_world->findActor(actorName); 
	if (m_actor.expired())
	{
		return;
	}
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

	BaseActor::onMessage(message, parameter);
}