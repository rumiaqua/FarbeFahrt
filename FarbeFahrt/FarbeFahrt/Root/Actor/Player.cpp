#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"
# include "Utility/Debug.h"
# include "Utility/Vector3.h"

Player::Player(IWorld& world, const Vector3& position) :
BaseActor(world, "Player", position, Vector3(0.0f, DX_PI_F, 0.0f))
, capsule(position, position, 5.0f)
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
	Vector3 moveVec;
	// カメラ座標
	const Vector3 cameraPos = world->findCamera()->getPosition();
	// カメラのY回転量
	const float cameraRotateY = world->findCamera()->getRotation().y;
	// 前方ベクトル
	Vector3 frontVec = position - cameraPos;
	// 左方ベクトル
	Vector3 leftVec = Vector3::cross(frontVec, Vector3::up());

	// XZ平面に射影して正規化
	leftVec.y = 0;
	leftVec.normalize();
	frontVec.y = 0;
	frontVec.normalize();

	if (Input::isClicked(KEY_INPUT_SPACE))
	{
		SE::playSE("bang");
	}

	// 移動処理
	if (Input::isPressed(KEY_INPUT_A))
	{
		moveVec += leftVec * moveSpeed;
	}
	if (Input::isPressed(KEY_INPUT_D))
	{
		moveVec -= leftVec * moveSpeed;
	}

	// 移動量が0でなければ移動処理とモデル操作
	if (moveVec.lengthSquared() != 0.0f)
	{
		// 平行移動
		position += moveVec;
		// 移動量に合わせてモデルを回転
		float angle =
			Vector3::angle(frontVec, moveVec) *
			static_cast<float>(Math::sign(Vector3::cross(frontVec, moveVec).y));
		rotation.y = cameraRotateY - angle + DX_PI_F;

		state = PlayerState::walking;
	}
	else
	{
		state = PlayerState::standing;
	}
}
void Player::onDraw(Renderer& render)const
{
	//ここで描画方法変えられますよ
	render.drawSkinModel("Player", position, rotation,(int)state,1.0f);
}
