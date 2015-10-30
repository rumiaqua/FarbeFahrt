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

	cameraMatrix.targetPos = { 0.0f, 20.0f, -30.0f };
	cameraMatrix.currentPos = cameraMatrix.targetPos;

	cameraMatrix.targetRot = { 0.0f, 15.0f, 0.0f };
	cameraMatrix.currentRot = cameraMatrix.targetRot;

	cameraState.chaseFlag = ChaseFlag::Void;
	cameraState.cameraMode = CameraMode::Init;

	actor = nullptr;	
}
void Camera::onUpdate()
{
	playerCheck();
	if (actor == nullptr)return;

	cameraSet();
}

void Camera::onDraw(Renderer& render)const
{

}

void Camera::chaseCamera()
{
	cameraMatrix.currentPos = getPosition();
	cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toFixCamera();
}

void Camera::fadeInCamera()
{
	cameraMatrix.currentPos = getPosition();
	t = 0;
	cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
	cameraState.chaseFlag = ChaseFlag::Move;
	cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeOutCamera()
{
	cameraMatrix.currentPos = getPosition();
	cameraMatrix.targetPos = { 0.0f, 140.0f, -150.0f };
	cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	cameraMatrix.targetRot = { 0.0f, 0.0f, 0.0f };
	cameraState.cameraMode = CameraMode::Default;
}

void Camera::fadeInFixCamera()
{
	actorCheck(actor->getName().toNarrow());
	if (actor == nullptr)return;

	cameraMatrix.currentPos = getPosition();
	cameraMatrix.targetPos = getPosition();
	t = 0;
	cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
	cameraState.chaseFlag = ChaseFlag::Stay;
	cameraState.cameraMode = CameraMode::Default;
}

void Camera::lockCamera()
{
	actorCheck(actor->getName().toNarrow());
	if (actor == nullptr)return;

	cameraMatrix.currentRot = memory_cast<Vector3>(GetCameraTarget());
	cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toPlayerCamera();
}

void Camera::defaultCamera()
{
	if (cameraState.chaseFlag == ChaseFlag::Move)
	{
		cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
		cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
		if (t >= 1)
		{
			cameraState.chaseFlag = ChaseFlag::Void;
			cameraState.cameraMode = CameraMode::Chase;
		}
	}
	else if (cameraState.chaseFlag == ChaseFlag::Stay)
	{
		cameraMatrix.targetPos = getPosition();
		cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
		if (t >= 1)
		{
			cameraState.chaseFlag = ChaseFlag::Void;
			cameraState.cameraMode = CameraMode::LockAt;
		}
	}
	else
	{
		if (t >= 1)
		{
		//移行できるカメラ
		toPlayerCamera();
		toFixCamera();
	}
}
}

void Camera::initCamera()
{
	cameraMatrix.targetPos = actor->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	cameraMatrix.targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
	getPosition() = cameraMatrix.targetPos;

	SetCameraPositionAndTarget_UpVecY(getPosition(), cameraMatrix.targetRot);

	cameraState.cameraMode = CameraMode::Chase;
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

	funcs.at(cameraState.cameraMode)();

	t += 1 / (60.0f * SECOND);
	t = t > 1.0f ? 1.0f : t;
	getPosition() = Vector3::Lerp(cameraMatrix.currentPos, cameraMatrix.targetPos, static_cast<float>(Math::Sin(Math::HALF_PI * t)));
	Vector3 focus = Vector3::Lerp(cameraMatrix.currentRot, cameraMatrix.targetRot, static_cast<float>(Math::Sin(Math::HALF_PI * t)));

	SetCameraPositionAndTarget_UpVecY(getPosition(), focus);
}

//キー：Zで本視点
void Camera::toBookCamera()
{
	if (Input::IsClicked(KEY_INPUT_Z))
	{
		t = 0;
		cameraState.cameraMode = CameraMode::FadeOut;
	}
}

//キー：Xでプレイヤー視点
void Camera::toPlayerCamera()
{
	if (Input::IsClicked(KEY_INPUT_X))
	{
		cameraState.cameraMode = CameraMode::FadeIn;
	}
}

//キー：Cでカメラ固定回転
void Camera::toFixCamera()
{
	if (Input::IsClicked(KEY_INPUT_C))
	{
		cameraState.cameraMode = CameraMode::FadeInFix;
	}
}

void Camera::playerCheck()
{
	actorCheck("Player");
}

void Camera::actorCheck(const std::string actorName)
{
	actor = world->findActor(actorName);
}