#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"
# include "Utility/Debug.h"
# include "Utility/Vector3.h"

Player::Player(IWorld& world, const Vector3& position) :
BaseActor(world, "Player", position, Matrix::rotation(Vector3::up(), Math::Pi))
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
	// �ړ���
	Vector3 moveVec;
	// �J�������W
	const Vector3 cameraPos = world->findCamera()->getPosition();
	// �O���x�N�g��
	Vector3 frontVec = Vector3::forward();
	// �����x�N�g��
	Vector3 leftVec = Vector3::left();

	// XZ���ʂɎˉe���Đ��K��
	leftVec.y = 0;
	leftVec.normalize();
	frontVec.y = 0;
	frontVec.normalize();

	if (Input::isClicked(KEY_INPUT_SPACE))
	{
		SE::playSE("bang");
	}

	// �ړ�����
	if (Input::isPressed(KEY_INPUT_A))
	{
		moveVec += leftVec * moveSpeed;
	}
	if (Input::isPressed(KEY_INPUT_D))
	{
		moveVec -= leftVec * moveSpeed;
	}
	if (Input::isPressed(KEY_INPUT_W))
	{
		moveVec += frontVec * moveSpeed;
	}
	if (Input::isPressed(KEY_INPUT_S))
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
	render.drawSkinModel("Player", getPosition(), getRotation(),(int)state,1.0f);
}