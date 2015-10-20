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
	// �ړ���
	Vector3 moveVec;
	// �J�������W
	const Vector3 cameraPos = world->findCamera()->getPosition();
	// �J������Y��]��
	const float cameraRotateY = world->findCamera()->getRotation().y;
	// �O���x�N�g��
	Vector3 frontVec = position - cameraPos;
	// �����x�N�g��
	Vector3 leftVec = Vector3::cross(frontVec, Vector3::up());

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

	// �ړ��ʂ�0�łȂ���Έړ������ƃ��f������
	if (moveVec.lengthSquared() != 0.0f)
	{
		// ���s�ړ�
		position += moveVec;
		// �ړ��ʂɍ��킹�ă��f������]
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
	//�����ŕ`����@�ς����܂���
	render.drawSkinModel("Player", position, rotation,(int)state,1.0f);
}
