#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"
#include "Utility/Debug.h"
#include "Utility/Vector3.h"

#include "Utility/Debug.h"

#include "Stand.h"
#include "Utility/MemoryCast.h"

Player::Player(IWorld& world, const Vector3& position) :
BaseActor(world, "Player", position, Matrix::Rotation(Vector3::Up(), Math::PI))
, capsule(position, position, 5.0f)
{
	moveSpeed = 1.5f;
	state = PlayerState::standing;
	moveFlag = false;

	Vector3 standPos = { 0,0,30 };
	//スタンドを生成
	this->addChild(std::make_shared<Stand>(world, standPos));

	stand = findChildren([](const BaseActor& actor) {return actor.getName() == "Stand"; });
}
void Player::onUpdate()
{
	playerInput();
	
	float messageParam = Math::toRadian(2.0);
	if (Input::isPressed(KEY_INPUT_Q))
	{
		stand->sendMessage("Rotation", &messageParam);
	}

	BaseActor::onUpdate();
}

void Player::playerInput()
{
	// 移動量
	Vector3 moveVec;
	// 前方ベクトル
	Vector3 frontVec = Vector3::Forward();
	// 左方ベクトル
	Vector3 leftVec = Vector3::Left();

	// XZ平面に射影して正規化
	leftVec.y = 0;
	leftVec.normalize();
	frontVec.y = 0;
	frontVec.normalize();

	if (Input::IsClicked(KEY_INPUT_SPACE))
	{
		SE::playSE("bang");
	}

	// 移動処理
	if (Input::IsPressed(KEY_INPUT_A))
	{
		moveVec += leftVec * moveSpeed;
	}
	if (Input::IsPressed(KEY_INPUT_D))
	{
		moveVec -= leftVec * moveSpeed;
	}
	if (Input::IsPressed(KEY_INPUT_W))
	{
		moveVec += frontVec * moveSpeed;
	}
	if (Input::IsPressed(KEY_INPUT_S))
	{
		moveVec -= frontVec * moveSpeed;
	}

	// 移動量が0でなければ移動処理とモデル操作
	if (moveVec.lengthSquared() != 0.0f)
	{
		// 平行移動
		getPosition() += moveVec;

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
	render.drawSkinModel("Player", getPosition(), getRotation(), (int)state, 1.0f);

	BaseActor::onDraw(render);
}