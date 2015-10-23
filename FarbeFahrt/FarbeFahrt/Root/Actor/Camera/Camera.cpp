#include "Camera.h"
#include "Actor/Enemy.h"
#include <memory>
#include "Utility/Math.h"

# include "Utility/Vector3.h"
# include "Utility/MemoryCast.h"
#include "Utility/MemoryCast.h"
#include "Utility/String.h"

#include "Utility/Debug.h"

Camera::Camera(IWorld& world) :
BaseActor(world, "Camera", Vector3::zero(), Vector3::zero())
{
	ang = 0.0f;
	focusRot = { 0, 0, 0 };

	SetCameraNearFar(1.0f, 12000.0f);
	SetCursorPos(nScreenCenterX, nScreenCenterY);

	targetPos = { 0.0f, 20.0f, -30.0f };
	currentPos = targetPos;

	targetRot = { 0.0f, 15.0f, 0.0f };
	currentRot = targetRot;

	second = 1;

	chaseFlag = ChaseFlag::Void;
	cameraMode = CameraMode::Init;

	actor = nullptr;

	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Chase, [this](){ this->chaseCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeIn, [this](){ this->fadeInCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeOut, [this](){ this->fadeOutCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Default, [this](){ this->defaultCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeInFix, [this](){ this->fadeInFixCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::LockAt, [this](){ this->lockCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Init, [this](){ this->initCamera(); }));
}
void Camera::onUpdate()
{
	playerCheck();
	if (player == nullptr)return;

	cameraSet();
}

void Camera::angleReset(float &ang)
{
	if (abs(ang) >= DX_PI_F * 2)
	{
		ang = fmod(ang, DX_PI_F * 2);
		//ang = 0.0f;
		printfDx("%f\n", ang);
	}
}

void Camera::rotate(float &x, float &z, const float ang, const float targetX, const float targetZ)
{
	const float ox = x - targetX, oy = z - targetZ;
	x = ox * cos(ang) + oy * sin(ang);
	z = ox * -sin(ang) + oy * cos(ang);
	x += targetX;
	z += targetZ;
}

void Camera::onDraw(Renderer& render)const
{
}

void Camera::chaseCamera()
{
	currentPos = position;
	targetPos = player->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	currentRot = memory_cast<Vector3>(GetCameraTarget());
	targetRot = player->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toFixCamera();
}

void Camera::fadeInCamera()
{
	currentPos = position;
	t = 0;
	targetPos = playerPos + Vector3(0.0f, 20.0f, -30.0f);
	currentRot = memory_cast<Vector3>(GetCameraTarget());
	targetRot = playerPos + Vector3(0.0f, 15.0f, 0.0f);
	chaseFlag = ChaseFlag::Move;
	cameraMode = CameraMode::Default;
}

void Camera::fadeOutCamera()
{
	currentPos = position;
	targetPos = { 0.0f, 140.0f, -150.0f };
	currentRot = memory_cast<Vector3>(GetCameraTarget());
	targetRot = { 0.0f, 0.0f, 0.0f };
	cameraMode = CameraMode::Default;
}

void Camera::fadeInFixCamera()
{
	actorCheck(actor->getName());
	if (actor == nullptr)return;

	currentPos = position;
	targetPos = position;
	t = 0;
	currentRot = memory_cast<Vector3>(GetCameraTarget());
	targetRot = actorPos + Vector3(0.0f, 15.0f, 0.0f);
	chaseFlag = ChaseFlag::Stay;
	cameraMode = CameraMode::Default;
}

void Camera::lockCamera()
{
	actorCheck(actor->getName());
	if (actor == nullptr)return;

	currentRot = memory_cast<Vector3>(GetCameraTarget());
	targetRot = actor->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	//移行できるカメラ
	toBookCamera();
	toPlayerCamera();
}

void Camera::defaultCamera()
{
	if (chaseFlag == ChaseFlag::Move)
	{
		targetPos = player->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
		targetRot = player->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
		if (t >= 1)
		{
			chaseFlag = ChaseFlag::Void;
			cameraMode = CameraMode::Chase;
		}
	}
	else if (chaseFlag == ChaseFlag::Stay)
	{
		targetPos = position;
		targetRot = player->getPosition() + Vector3(0.0f, 15.0f, 0.0f);
		if (t >= 1)
		{
			chaseFlag = ChaseFlag::Void;
			cameraMode = CameraMode::LockAt;
		}
	}
	else
	{
		//移行できるカメラ
		toPlayerCamera();
		toFixCamera();
	}
}

void Camera::initCamera()
{
	targetPos = player->getPosition() + Vector3(0.0f, 20.0f, -30.0f);
	targetRot = player->getPosition() + Vector3(0.0f, 15.0f, 0.0f);

	rotate(position.x, position.z, ang, focusRot.x, focusRot.z);
	position = targetPos;
	focusRot = targetRot;

	SetCameraPositionAndTarget_UpVecY(position, focusRot);

	cameraMode = CameraMode::Chase;
}

void Camera::cameraSet()
{
	funcs.at(cameraMode)();

	rotate(position.x, position.z, ang, focusRot.x, focusRot.z);
	t += 1 / (60.0f * second);
	t = t > 1.0f ? 1.0f : t;
	position = Vector3::lerp(currentPos, targetPos, static_cast<float>(Math::sin(Math::HalfPi * t)));
	focusRot = Vector3::lerp(currentRot, targetRot, static_cast<float>(Math::sin(Math::HalfPi * t)));

	SetCameraPositionAndTarget_UpVecY(position, focusRot);
}

//キー：Zで本視点
void Camera::toBookCamera()
{
	if (Input::isClicked(KEY_INPUT_Z))
	{
		t = 0;
		cameraMode = CameraMode::FadeOut;
	}
}

//キー：Xでプレイヤー視点
void Camera::toPlayerCamera()
{
	playerCheck();
	if (player == nullptr)return;

	if (Input::isClicked(KEY_INPUT_X))
	{
		playerPos = player->getPosition();
		cameraMode = CameraMode::FadeIn;
	}
}

//キー：Cでカメラ固定回転
void Camera::toFixCamera()
{
	actorCheck("Player");
	if (actor == nullptr)return;

	if (Input::isClicked(KEY_INPUT_C))
	{
		actorPos = actor->getPosition();
		cameraMode = CameraMode::FadeInFix;
	}
}

void Camera::playerCheck()
{
	player = world->findActor("Player");
}

void Camera::actorCheck(const std::string actorName)
{
	actor = world->findActor(actorName);
}