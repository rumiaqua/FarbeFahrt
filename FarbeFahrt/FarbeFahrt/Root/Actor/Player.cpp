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

#include "Actor/Particle/LightParticleGenerator.h"

#include "Utility/String.h"

# include "Manager/MessageManager.h"

# include "Collision/ModelCollider.h"

namespace
{
	constexpr float OBSTACLE_DISTANCE = 5.0f;
	const float XLim = 142.0f;
	const float ZLim = 110.0f;
	const float Correction = 145.0f / 2.0f - 4.0f;
}

Player::Player(IWorld& world, const Vector3& position, const std::vector<Vector4>& noEntries)
	: BaseActor(world, "Player", position, Matrix::Rotation(Vector3::Up(), Math::PI / 2),
		std::make_unique<Capsule>(Vector3(0, 0, 0), Vector3(0, 10, 0), 5.0f)
		)
	, m_canControl(false)
	, m_noEntries(noEntries)
{
	m_moveSpeed = 1.5f;
	m_state = PlayerState::standing;
	m_moveFlag = false;
	m_frame = 0;
}
void Player::onUpdate()
{
	m_previousPosition = m_pose.position;
	++m_frame;

	m_pose.position.y -= 2.0f;

	animate(m_canControl ? playerInput() : Vector3::Zero());

	// 移動制限
	m_pose.position.x = (float)Math::Clamp(m_pose.position.x, -XLim - Correction, XLim - Correction);
	m_pose.position.z = (float)Math::Clamp(m_pose.position.z, -ZLim, ZLim);

	// 立ち入り禁止判定
	for (auto&& noEntry : m_noEntries)
	{
		float& x = m_pose.position.x;
		float& z = m_pose.position.z;
		bool entryX = Math::IsContains(x, noEntry.x, noEntry.y);
		bool entryZ = Math::IsContains(z, noEntry.z, noEntry.w);
		if (entryX && entryZ)
		{
			m_pose.position = m_previousPosition;
		}
	}

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
}

void Player::onDraw(Renderer& renderer)const
{
	Debug::Println(String::Create("PlayerPosition : ", m_pose.position.ToString()));
	//ここで描画方法変えられますよ
	std::string name = "Player";
	name += StoryManager::get(BitFlag::RIDEON) ? "Riding" : "";
	renderer.drawSkinModel(name, getPosition(), getRotation(), (int)m_state, m_frame, true);
	BaseActor::onDraw(renderer);
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
			m_pose.position = otherPos + movement;
			m_pose.position.y += 2.0f;
		}
	}

	if (message == "HitBackground")
	{
		m_pose = m_previousPose;
	}

	if (message == "HitGround")
	{
		Vector3* pos = static_cast<Vector3*>(parameter);
		m_pose.position = *pos;
	}
	if (message == "StopControl")
	{
		if (*(bool*)parameter)
		{
			kill();
		}
		m_canControl = false;
	}
	if (message == "StartControl")
	{
		m_canControl = true;
	}
	if (message == "Translate")
	{
		Vector3* translate = static_cast<Vector3*>(parameter);
		m_pose.position += *translate;
	}
	if (message == "SetPosition")
	{
		Vector3* position = static_cast<Vector3*>(parameter);
		m_pose.position = *position;
	}

	if (message == "RefreshNoEntry")
	{
		m_noEntries.clear();
	}

	BaseActor::onMessage(message, parameter);
}
