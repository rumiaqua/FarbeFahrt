#include "Camera.h"
#include "Actor/Enemy.h"
#include <memory>
Camera::Camera(IWorld& world) :
BaseActor(world, "Camera", VGet(0, 0, 0), VGet(0, 0, 0))
{
	ang = 0.0f;
	targetPos = { 0, 0, 0 };
	SetCameraNearFar(1.0f, 12000.0f);
	SetCursorPos(nScreenCenterX, nScreenCenterY);
}
void Camera::onUpdate()
{
	auto player = world->findActor("Player");
	if (player == nullptr)return;
	
	if (Input::isPressed(KEY_INPUT_Z))
	{
		position.z--;
	}
	else
	{
	rotation = VGet(0.0f, ang, 0.0f);
	position = VAdd(player->getPosition(), VGet(0.0f, 20.0f, -30.0f));
	
	targetPos = VAdd(player->getPosition(), VGet(0.0f, 15.0f, 0.0f));

	//カメラ移動処理
	GetCursorPos(&mousePos);
		if ((mousePos.x) < nScreenCenterX - 1.0f)//マウスが左に動いたとき
		{
			ang -= (nScreenCenterX - mousePos.x)*0.001f;
		}
		if ((mousePos.x) > nScreenCenterX + 1.0f)//マウスが右に動いたとき
		{
			ang += (mousePos.x - nScreenCenterX)*0.001f;
		}
		angleReset(ang);
		SetCursorPos(nScreenCenterX, nScreenCenterY);
	}

	rotate(position.x, position.z, ang, targetPos.x, targetPos.z);

	//カメラ移動処理ここまで
	SetCameraPositionAndTarget_UpVecY(position, targetPos);

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