#include "Player.h"

#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"
#include "Utility/Debug.h"
#include "Utility/Vector3.h"
#include "Utility/Debug.h"
#include "Utility/MemoryCast.h"
#include "Utility/StoryManager/StoryManager.h"
# include "Utility/HandleList.h"
# include "Utility/SingletonFinalizer.h"

#include "Utility/String.h"

# include "Manager/MessageManager.h"

# include "Collision/ModelCollider.h"

namespace
{
	constexpr float OBSTACLE_DISTANCE = 5.0f;
	const float XLim = 142.0f;
	const float ZLim = 110.0f;
	const float correction = 145.0f / 2.0f - 4.0f;
}

Player::Player(IWorld& world, const Vector3& position)
	: BaseActor(world, "Player", position, Matrix::Rotation(Vector3::Up(), Math::PI / 2),
		std::make_unique<Capsule>(Vector3(0, 0, 0), Vector3(0, 10, 0), 5.0f)
		)
	, m_canControl(true)
	, m_isFallDown(false)
{
	m_moveSpeed = 1.5f;
	m_state = PlayerState::standing;
	m_moveFlag = false;
	m_frame = 0;
}
void Player::onUpdate()
{
	Vector3 moveVec;

	++m_frame;

	if (m_canControl)
	{
		moveVec = playerInput();
	}

	if (Input::IsClicked(KEY_INPUT_SPACE))
	{
		int i = 2;
		if (auto p = m_world->findActor("forestBGround"))
		{
			p->sendMessage("Animate", &i);
		}
	}

	if (m_isFallDown)
	{
		if (auto handle = Singleton<HandleList>::Instance().getHandle("Player"))
		{
			float current = MV1GetAttachAnimTime(handle, 0);
			float total = MV1GetAnimTotalTime(handle, 0);
			if (current < m_previousFrame ||
				current > total)
			{
				m_frame = 0;
				m_canControl = true;
				m_isFallDown = false;
			}
			m_previousFrame = current;
		}
	}

	animate(moveVec);

	BaseActor::onUpdate();
}

Vector3 Player::playerInput()
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

	// 移動処理
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

	// 重力
	m_pose.position.y -= 2.0f;

	// 移動制限
	m_pose.position.x = (float)Math::Clamp(m_pose.position.x, -XLim - correction, XLim - correction);
	m_pose.position.z = (float)Math::Clamp(m_pose.position.z, -ZLim, ZLim);

	if (Input::IsClicked(KEY_INPUT_1))
	{
		m_pose.position = m_world->findActor("PlayerSpawner")->getPosition();
	}

	return moveVec;
}
void Player::animate(const Vector3& moveVec)
{
	// 移動量が0でなければ移動処理とモデル操作
	if (moveVec.lengthSquared() != 0.0f && m_canControl)
	{
		// 平行移動
		getPosition() += moveVec;

		Vector3 direction = Vector3::Normalize(moveVec);
		double angle = Vector3::Angle(Vector3::Forward(), direction);
		double sign = Math::Sign(Vector3::Cross(Vector3::Forward(), direction).y);
		m_pose.rotation = Matrix::Rotation(Vector3::Up(), angle * sign + Math::PI);

		m_state = PlayerState::walking;
	}
	else
	{
		m_state = PlayerState::standing;
	}

	if (m_isFallDown)
	{
		m_state = PlayerState::Bwalking;
	}
}

void Player::fallDown()
{
	m_frame = 0.0f;
	MV1SetAttachAnimTime(Singleton<HandleList>::Instance().getHandle("Player"), 0, 0.0f);
	m_previousFrame = 0.0f;
	m_isFallDown = true;
	m_canControl = false;
}

void Player::onDraw(Renderer& render)const
{
	Debug::Println(String::Create("Elapsed Time : ", MV1GetAttachAnimTime(Singleton<HandleList>::Instance().getHandle("Player"), 0)));
	// m_previousFrame
	//ここで描画方法変えられますよ
	render.drawSkinModel("Player", getPosition(), getRotation(), (int)m_state, m_frame, true);
	BaseActor::onDraw(render);
}

void Player::onMessage(const std::string& message, void* parameter)
{
	if (message == "HitObstacle")
	{
		BaseActor* actor = static_cast<BaseActor*>(parameter);
		if (isCollide(actor))
		{
			float D = static_cast<Capsule*>(m_shape.get())->radius + static_cast<Capsule* const>(actor->getShape())->radius + OBSTACLE_DISTANCE;
			Vector3 ownPos = m_pose.position;
			Vector3 otherPos = actor->getPosition();
			Vector3 direction = Vector3::Normalize(ownPos - otherPos);
			Vector3 normalize = Vector3::Normalize(direction * Vector3(1, 0, 1));
			otherPos.y = ownPos.y;
			Vector3 movement = normalize * D;

			Debug::Println(String::Create("myName:", m_name));
			Debug::Println(String::Create("Name:", actor->getName()));
			Debug::Println(String::Create("direction:", direction.ToString()));

			Debug::Println(String::Create("normalize:", normalize.ToString()));
			Debug::Println(String::Create("movement:", movement.ToString()));
			getPosition() = otherPos + movement;

			//m_pose.position.y += 2.0f;
		}
	}

	if (message == "HitGround")
	{
		Vector3* pos = static_cast<Vector3*>(parameter);
		m_pose.position = *pos;
		Debug::Println("ゆかのなかにいる");
	}
	if (message == "StopControl")
	{
		if ((bool*)parameter)
		{
			m_canControl = false;
			kill();
		}
		else
		{
			m_canControl = false;
		}
	}
	if (message == "StartControl")
	{
		m_canControl = true;
	}

	if (message == "FallDown")
	{
		fallDown();
	}

	BaseActor::onMessage(message, parameter);
}
