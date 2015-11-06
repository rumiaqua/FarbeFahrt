#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"
#include "Utility/Debug.h"
#include "Utility/Vector3.h"

#include "Utility/Debug.h"

#include "Stand.h"
#include "Utility/MemoryCast.h"

Player::Player(IWorld& world, const Vector3& position)
	: BaseActor(world, "Player", position, Matrix::Rotation(Vector3::Up(), Math::PI))
	, m_capsule(position, position, 5.0f)
{
	m_moveSpeed = 1.5f;
	m_state = PlayerState::standing;
	m_moveFlag = false;
	m_flame = 0;
}
void Player::onUpdate()
{
	playerInput();
	
	m_flame++;

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
		SE::Play("bang");
	}

	// �ړ�����
	if (Input::IsPressed(KEY_INPUT_A))
	{
		moveVec += leftVec * m_moveSpeed;
	}
	if (Input::IsPressed(KEY_INPUT_D))
	{
		moveVec -= leftVec * m_moveSpeed;
	}
	if (Input::IsPressed(KEY_INPUT_W))
	{
		moveVec += frontVec * m_moveSpeed;
	}
	if (Input::IsPressed(KEY_INPUT_S))
	{
		moveVec -= frontVec * m_moveSpeed;
	}

	// �ړ��ʂ�0�łȂ���Έړ������ƃ��f������
	if (moveVec.lengthSquared() != 0.0f)
	{
		// ���s�ړ�
		getPosition() += moveVec;

		m_state = PlayerState::walking;
	}
	else
	{
		m_state = PlayerState::standing;
	}
}
void Player::onDraw(Renderer& render)const
{
	//�����ŕ`����@�ς����܂���
	render.drawSkinModel("Player", getPosition(), getRotation(), (int)m_state, m_flame);

	BaseActor::onDraw(render);
}