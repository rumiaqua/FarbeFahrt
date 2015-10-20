#include "Camera.h"
#include "Actor/Enemy.h"
#include <memory>
#include "Utility/Math.h"

# include "Utility/Vector3.h"
# include "Utility/MemoryCast.h"

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

	chaseFlag = false;
	cameraMode = CameraMode::Init;

	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Chase, [this](){ this->chaseCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeIn, [this](){ this->fadeInCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::FadeOut, [this](){ this->fadeOutCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Default, [this](){ this->defaultCamera(); }));
	funcs.insert(std::make_pair<CameraMode, Func>(CameraMode::Init, [this](){ this->initCamera(); }));
}
void Camera::onUpdate()
{
	playerCheck();

	cameraControl();
	cameraSet();

	/*clsDx();
	printfDx("pos_.x:%f pos_.y:%f pos_.z:%f\n", position.x, position.y, position.z);
	printfDx("target.x:%f target.y:%f target.z:%f\n", targetPos.x, targetPos.y, targetPos.z);
	printfDx("cur.x:%f cur.y:%f cur.z:%f\n", currentPos.x, currentPos.y, currentPos.z);
	printfDx("t:%f\n", t);*/
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
	playerCheck();

	dif = VSub(targetPos, position);
		currentPos = position;
	targetPos = VAdd(player->getPosition(), VGet(0.0f, 20.0f, -30.0f));
	currentRot = GetCameraTarget();
	targetRot = VAdd(player->getPosition(), VGet(0.0f, 15.0f, 0.0f));
	rotation = VGet(0.0f, ang, 0.0f);
	}

void Camera::fadeInCamera()
	{
	playerCheck();

	dif = VSub(targetPos, position);
	currentPos = position;
	targetPos = VAdd(playerPos, VGet(0.0f, 20.0f, -30.0f));
	currentRot = GetCameraTarget();
	targetRot = VAdd(playerPos, VGet(0.0f, 15.0f, 0.0f));
	rotation = VGet(0.0f, ang, 0.0f);
	chaseFlag = true;
	cameraMode = CameraMode::Default;
	}
	
void Camera::fadeOutCamera()
	{
	playerCheck();

	dif = VSub(targetPos, position);
		currentPos = position;
	targetPos = { 0.0f, 140.0f, -150.0f };
	currentRot = GetCameraTarget();
	targetRot = { 0.0f, 0.0f, 0.0f };
	cameraMode = CameraMode::Default;
	}

void Camera::defaultCamera()
{
	playerCheck();

	if (chaseFlag == true)
	{
		targetPos = VAdd(player->getPosition(), VGet(0.0f, 20.0f, -30.0f));
		targetRot = VAdd(player->getPosition(), VGet(0.0f, 15.0f, 0.0f));
		if (t >= 1)
	{
			chaseFlag = false;
			cameraMode = CameraMode::Chase;
	}
	}
}

void Camera::initCamera()
	{
	playerCheck();

	targetPos = VAdd(player->getPosition(), VGet(0.0f, 20.0f, -30.0f));
	targetRot = VAdd(player->getPosition(), VGet(0.0f, 15.0f, 0.0f));
	rotation = VGet(0.0f, ang, 0.0f);

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
	if (Input::isClicked(KEY_INPUT_Z) && cameraMode == CameraMode::Chase)
	{
		cameraMode = CameraMode::FadeOut;
		t = 0;
	}
}

//キー：Xでプレイヤー視点
void Camera::toPlayerCamera()
{
	playerCheck();

	if (Input::isClicked(KEY_INPUT_X) && cameraMode == CameraMode::Default)
	{
		playerPos = player->getPosition();
		cameraMode = CameraMode::FadeIn;
		t = 0;
	}
	}

void Camera::cameraControl()
{
	if (t < 1)
	{
		return;
}
	else
{
		toBookCamera();
		toPlayerCamera();
	}
}

void Camera::playerCheck()
{
	player = world->findActor("Player");
	if (player == nullptr)return;
}