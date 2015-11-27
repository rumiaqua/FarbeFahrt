#include "Field.h"

# include "Collision/ModelCollider.h"

# include "Utility/Math.h"
# include "Utility/SingletonFinalizer.h"
# include "Utility/HandleList.h"

# include "Utility/Debug.h"
# include "Utility/StoryManager/StoryManager.h"

namespace
{
	constexpr float ANIMATION_FRAME = 180.0f;
}

Field::Field(IWorld& world, const std::string& name, const Vector3& position, float scale)
	:BaseActor(world, name, position, Matrix::identity(),
		std::make_unique<ModelCollider>(name)), m_scale(scale)
	, m_elapsedTime(0.0f)
	, m_animationNumber(0)
	, m_isAnimating(false)
{

}

void Field::onUpdate()
{
	if (m_isAnimating)
	{
		m_elapsedTime += 1.0f;
		m_isAnimating = m_elapsedTime < ANIMATION_FRAME;
		m_elapsedTime = Math::Min({ m_elapsedTime, ANIMATION_FRAME });

# define Open 0
		if (m_animationNumber == Open &&
			!m_isAnimating)
		{
			/*for (auto&& spawner : m_world->findActors("PlayerSpawner"))
			{
				spawner->sendMessage("PlayerSpawn", nullptr);
			}*/
			m_world->findGroup(ActorTag::Player)->eachChildren([] (BaseActor& actor) { actor.sendMessage("PlayerSpawn", nullptr); });
			m_world->findCamera()->sendMessage("toPlayerCamera", nullptr);
			StoryManager::set(BitFlag::NEXT);
		}
# undef Open

# define Close 1
		if (m_animationNumber == Close &&
			!m_isAnimating)
		{
			kill();
		}
# undef Close
	}

	BaseActor::onUpdate();
}
void Field::onDraw(Renderer& render) const
{
	render.setScale(m_name, VGet(m_scale, m_scale, m_scale));

	float t = Math::Min({ m_elapsedTime / ANIMATION_FRAME, 0.9999f });
	render.drawSkinModel(m_name, m_pose, m_animationNumber, t);

	BaseActor::onDraw(render);
}

void Field::onMessage(const std::string& message, void* parameter)
{
	if (message == "onCollide")
	{
		BaseActor* actor = static_cast<BaseActor*>(parameter);
		if (isCollide(actor))
		{
			const Vector3& pos = actor->getPosition();
			Debug::Println(pos.ToString());
			std::string& name = static_cast<ModelCollider*>(m_shape.get())->name;
			int handle = Singleton<HandleList>::Instance().getHandle(name);

			Vector3 start = pos + Vector3::Up() * 50.0f;
			Vector3 end = pos + Vector3::Down() * 1.0f;

			MV1RefreshCollInfo(handle);
			MV1_COLL_RESULT_POLY dim = MV1CollCheck_Line(handle, -1, start, end);
			if (dim.HitFlag == TRUE)
			{
				HITRESULT_LINE result = HitCheck_Line_Triangle(
					start, end, dim.Position[0], dim.Position[1], dim.Position[2]);

				Vector3 fixPos = result.Position;

				actor->sendMessage("HitGround", (void*)&fixPos);
			}
		}
	}

	if (message == "OpenAnimate")
	{
		// 開くアニメーション
		open();
	}

	if (message == "CloseAnimate")
	{
		// 閉じるアニメーション
		close();
	}

	BaseActor::onMessage(message, parameter);
}

void Field::open()
{
	m_elapsedTime = 0.0f;
	m_animationNumber = 0;
	m_isAnimating = true;
}

void Field::close()
{
	m_elapsedTime = 0.0f;
	m_animationNumber = 1;
	m_isAnimating = true;
}
