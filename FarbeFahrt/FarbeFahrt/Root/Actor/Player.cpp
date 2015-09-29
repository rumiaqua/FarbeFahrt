#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"

Player::Player(IWorld& world, const VECTOR position) :
BaseActor(world, "Player", position, VGet(0, DX_PI_F, 0))
{
	moveSpeed = 1.5f;
	state = PlayerState::standing;
	moveFlag = false;
}
void Player::onUpdate()
{
	playerInput();
}
void Player::playerInput()
{
	// 移動量
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);
	// カメラ座標
	const VECTOR cameraPos = world->findCamera()->getPosition();
	// カメラのY回転量
	const float cameraRotateY = world->findCamera()->getRotation().y;
	// 前方ベクトル
	VECTOR frontVec = VSub(position, cameraPos);
	// 左方ベクトル
	VECTOR leftVec = VCross(frontVec, VGet(0.0f, 1.0f, 0.0f));

	// XZ平面に射影して正規化
	leftVec.y = 0;
	leftVec = VNorm(leftVec);
	frontVec.y = 0;
	frontVec = VNorm(frontVec);

	if (Input::isClicked(KEY_INPUT_SPACE))
	{
		SE::instance().playSE("TEST");
	}

	// 移動処理
	if (Input::isPressed(KEY_INPUT_W))
	{
		moveVec = VAdd(moveVec, VScale(frontVec, moveSpeed));
	}
	if (Input::isPressed(KEY_INPUT_A))
	{
		moveVec = VAdd(moveVec, VScale(leftVec, moveSpeed));
	}
	if (Input::isPressed(KEY_INPUT_S))
	{
		moveVec = VAdd(moveVec, VScale(frontVec, -moveSpeed));
	}
	if (Input::isPressed(KEY_INPUT_D))
	{
		moveVec = VAdd(moveVec, VScale(leftVec, -moveSpeed));
	}

	// 移動量が0でなければ移動処理とモデル操作
	if (Math::LengthSquared(moveVec) != 0.0f)
	{
		// 平行移動
		position = VAdd(position, moveVec);
		// 移動量に合わせてモデルを回転
		float angle = Math::Angle(frontVec, moveVec) * Math::Sign(VCross(frontVec, moveVec).y);
		rotation.y = cameraRotateY - angle + Math::ToRadian(180.0f);

		state = PlayerState::walking;
	}
	else
	{
		state = PlayerState::standing;
	}
void Player::onDraw(Renderer& render)const
{
	//ここで描画方法変えられますよ
	render.drawSkinModel("Player", position, rotation,(int)state,1.0f);
}