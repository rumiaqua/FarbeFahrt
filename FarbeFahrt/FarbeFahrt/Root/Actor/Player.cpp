#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"
#include "Utility/Debug.h"
#include "Utility/Vector3.h"
#include "Utility/Debug.h"
#include "Utility/MemoryCast.h"

# include "Collision/ModelCollider.h"

# include "Utility/SingletonFinalizer.h"
# include "Experimental/FlagManager.h"

Player::Player(IWorld& world, const Vector3& position)
	: BaseActor(world, "Player", position, Matrix::Rotation(Vector3::Up(), Math::PI),
		// std::make_unique<Sphere>(Vector3::Zero(), 10.0f)
		// std::make_unique<Triangle>(Vector3::Zero(), Vector3(-10, -20, 0), Vector3(10, -20, 0)))
		std::make_unique<Capsule>(Vector3(0, 0, 0), Vector3(0, 10, 0), 5.0f)
		// std::make_unique<Line>(Vector3(10, 0, 0), Vector3(-10, 0, 0))
		// std::make_unique<ModelCollider>("Player")
		)
{
	m_moveSpeed = 1.5f;
	m_state = PlayerState::standing;
	m_moveFlag = false;
	m_flame = 0;
}
void Player::onUpdate()
{
	playerInput();
	
	++m_flame;

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

		Vector3 direction = Vector3::Normalize(moveVec);
		float angle = Vector3::Angle(Vector3::Forward(), direction);
		float sign = Math::Sign(Vector3::Cross(Vector3::Forward(), direction).y);

		m_pose.rotation = Matrix::Rotation(Vector3::Up(), angle * sign + Math::PI);

		m_state = PlayerState::walking;
	}
	else
	{
		m_state = PlayerState::standing;
	}

	m_pose.position.y -= 2.0f;

	//if (getPosition().y < -100.0f)
	//{
	//	getPosition().y = -100.0f;
	//}

	if (Input::IsClicked(KEY_INPUT_1))
	{
		m_pose.position.x = 0;
		m_pose.position.y = 100;
		m_pose.position.z = 0;
	}

	if (Input::IsClicked(KEY_INPUT_2))
	{
		FlagManager::Set(Flag::NextStage, true);
	}
}
void Player::onDraw(Renderer& render)const
{
	//�����ŕ`����@�ς����܂���
	render.drawSkinModel("Player", getPosition(), getRotation(), (int)m_state, m_flame);

	BaseActor::onDraw(render);
}

void Player::onMessage(const String& message, void* parameter)
{
	if (message == "onCollide")
	{
		// Debug::Println("�Ȃɂ��ɂ������Ă��");
	}
	if (message == "HitGround")
	{
		Vector3* pos = static_cast<Vector3*>(parameter);
		m_pose.position = *pos;
		Debug::Println("�䂩�̂Ȃ��ɂ���");
	}
	if (message == "Goal")
	{
		// m_world->setFlag(1);
		Singleton<FlagManager>::Instance().Set(Flag::NextStage, true);
	}

	BaseActor::onMessage(message,parameter);
}
