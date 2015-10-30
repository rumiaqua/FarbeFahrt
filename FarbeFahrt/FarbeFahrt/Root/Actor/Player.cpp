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
	//�X�^���h�𐶐�
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
	// �ړ���
	Vector3 moveVec;
	// �O���x�N�g��
	Vector3 frontVec = Vector3::Forward();
	// �����x�N�g��
	Vector3 leftVec = Vector3::Left();

	// XZ���ʂɎˉe���Đ��K��
	leftVec.y = 0;
	leftVec.normalize();
	frontVec.y = 0;
	frontVec.normalize();

	if (Input::IsClicked(KEY_INPUT_SPACE))
	{
		SE::playSE("bang");
	}

	// �ړ�����
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

	// �ړ��ʂ�0�łȂ���Έړ������ƃ��f������
	if (moveVec.lengthSquared() != 0.0f)
	{
		// ���s�ړ�
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
	//�����ŕ`����@�ς����܂���
	render.drawSkinModel("Player", getPosition(), getRotation(), (int)state, 1.0f);

	BaseActor::onDraw(render);
}