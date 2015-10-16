#include "Camera.h"
#include "Actor/Enemy.h"
#include <memory>
#include "Utility/Math.h"

Camera::Camera(IWorld& world) :
BaseActor(world, "Camera", VGet(0, 0, 0), VGet(0, 0, 0))
{
	ang = 0.0f;
	focusRot = { 0, 0, 0 };

	SetCameraNearFar(1.0f, 12000.0f);
	SetCursorPos(nScreenCenterX, nScreenCenterY);

	targetPos = { 0.0f, 20.0f, -30.0f };
	currentPos = targetPos;

	targetRot = { 0.0f, 15.0f, 0.0f };
	currentRot = targetRot;

	focus = { 0, 0, 0 };

	second = 1;
}
void Camera::onUpdate()
{
	auto player = world->findActor("Player");
	if (player == nullptr)return;

	if (Input::isClicked(KEY_INPUT_Z))
	{
		dif = VSub(targetPos, position);
		currentPos = position;
		targetPos = { 0.0f, 140.0f, -150.0f };
		currentRot = GetCameraTarget();
		targetRot = { 0.0f, 0.0f, 0.0f };

		fadeFlag = true;

		t = 0;
	}

	if (Input::isClicked(KEY_INPUT_X))
	{
		dif = VSub(targetPos, position);	
		fadeFlag = false;

		t = 0;
	}
	
	if (fadeFlag == false)
	{
		currentPos = position;
		targetPos = VAdd(player->getPosition(), VGet(0.0f, 20.0f, -30.0f));
		currentRot = GetCameraTarget();
		targetRot = VAdd(player->getPosition(), VGet(0.0f, 15.0f, 0.0f));
		rotation = VGet(0.0f, ang, 0.0f);
	}

	/*if (Input::isPressed(KEY_INPUT_Z))
	{
	auto target = VSub(GetCameraTarget(),focus);
	focusRot = VAdd(focusRot, VScale(VNorm(target), 2));
	if (VSquareSize(target) < 2 * 2)
	{
	focusRot = focus;
	}
	}
	else
	{
	rotation = VGet(0.0f, ang, 0.0f);
	position = VAdd(player->getPosition(), VGet(0.0f, 20.0f, -30.0f));

	focusRot = VAdd(player->getPosition(), VGet(0.0f, 15.0f, 0.0f));
	rotate(position.x, position.z, ang, focusRot.x, focusRot.z);
	}*/

	rotate(position.x, position.z, ang, focusRot.x, focusRot.z);

	t += 1 / (60.0f * second);
	t = t > 1.0f ? 1.0f : t;
	position = Math::VLerp(currentPos, targetPos, t);
	focusRot = Math::VLerp(currentRot, targetRot, t);

	SetCameraPositionAndTarget_UpVecY(position, focusRot);

	clsDx();
	printfDx("pos_.x:%f pos_.y:%f pos_.z:%f\n", position.x, position.y, position.z);
	printfDx("target.x:%f target.y:%f target.z:%f\n", targetPos.x, targetPos.y, targetPos.z);
	printfDx("cur.x:%f cur.y:%f cur.z:%f\n", currentPos.x, currentPos.y, currentPos.z);
	printfDx("t:%f\n", t);
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