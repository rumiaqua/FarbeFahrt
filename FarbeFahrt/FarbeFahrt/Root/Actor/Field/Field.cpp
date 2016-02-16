#include "Field.h"

# include "Collision/ModelCollider.h"

# include "Utility/Math.h"
# include "Utility/SingletonFinalizer.h"
# include "Utility/HandleList.h"

# include "Utility/Debug.h"
# include "Utility/StoryManager/StoryManager.h"

# include "Manager/MessageManager.h"
# include "Manager/EndManager.h"

# include "Experimental/AnimateState.h"


namespace
{
	constexpr float ANIMATION_FRAME = 180.0f;
}

Field::Field(IWorld& world, const std::string& name, const Vector3& position, float scale, const std::string& transition)
	:BaseActor(world, name, position, Matrix::identity(),
		std::make_unique<ModelCollider>(name)), m_scale(scale)
	, m_elapsedTime(0.0f)
	, m_animationNumber(0)
	, m_isAnimating(false)
	, m_isReversed(false)
	, m_isBackground(false)
	, m_gimmick(false)
	, m_machine(transition)
	, m_current()
	, m_cameraProgress(false)
{

}

void Field::onUpdate()
{
	MessageManager::SetShow(false);

	auto camera = m_world->findCamera();
	if (camera == nullptr)return;
	camera->sendMessage("progress", &m_cameraProgress);

	if (m_isAnimating)
	{
		if (m_isReversed)
		{
			m_elapsedTime -= 1.0f;
			m_isAnimating = m_elapsedTime > 0.0f;
			m_elapsedTime = Math::Max({ m_elapsedTime, 0.0f });			
		}
		else
		{
			if (m_cameraProgress >= 1)
			{
				m_elapsedTime += 1.0f;
			}
			m_isAnimating = m_elapsedTime <= ANIMATION_FRAME;
			m_elapsedTime = Math::Min({ m_elapsedTime, ANIMATION_FRAME });
		}

		if (m_elapsedTime >= ANIMATION_FRAME)
		{
			m_world->findCamera()->sendMessage("toBookCamera", nullptr);
			MessageManager::SetShow(true);
		}

		if (m_current == "End" &&
			!m_isAnimating)
		{
			EndManager::SetEnd(true);
			MessageManager::SetShow(true);
		}

		if (m_current == "Open" &&
			!m_isAnimating)
		{
			m_world->findGroup(ActorTag::Player)->eachChildren([] (BaseActor& actor) { actor.sendMessage("PlayerSpawn", nullptr); });
			m_world->findCamera()->sendMessage("toPlayerCamera", nullptr);
			StoryManager::set(BitFlag::NEXT);
			MessageManager::SetShow(true);
		}

		if (m_current == "Close" &&
			!m_isAnimating)
		{
			kill();
		}
	}

	BaseActor::onUpdate();
}
void Field::onDraw(Renderer& renderer) const
{
	renderer.setScale(m_name, VGet(m_scale, m_scale, m_scale));

	float t = Math::Min({ m_elapsedTime / ANIMATION_FRAME, 0.99999f });
	renderer.drawSkinModel(m_name, m_pose, m_animationNumber, t,false);

	BaseActor::onDraw(renderer);
}

void Field::onMessage(const std::string& message, void* parameter)
{
	if (message == "onCollide")
	{
		BaseActor* actor = static_cast<BaseActor*>(parameter);
		if (isCollide(actor))
		{
			if (m_isBackground)
			{
				actor->sendMessage("HitBackground", nullptr);
				return BaseActor::onMessage(message, parameter);
			}

			const Vector3& pos = actor->getPosition();
			std::string& name = static_cast<ModelCollider*>(m_shape.get())->name;
			int handle = Singleton<HandleList>::Instance().getHandle(name);

			Vector3 start = pos + Vector3::Up() * 5.0f;
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

	if (message == "Animate")
	{
		const AnimateState& state = *(AnimateState*)parameter;
		animateProcess(state);
	}

	if (message == "WorkGimmick" && isGround())
	{
		m_previousAnimNo = *(int*)parameter;
		workGimmick(*(int*)parameter);
	}

	BaseActor::onMessage(message, parameter);
}

void Field::workGimmick(int commandNo)
{
	m_elapsedTime = 0.0f;
	m_animationNumber = commandNo;
	m_isReversed = false;
	m_isAnimating = true;
}

void Field::animateProcess(const AnimateState& state)
{
	Optional<AnimationTransitionMachine::AnimateState> next = m_machine.next(state.name, m_animationNumber);

	if (!next)
	{
		return;
	}

	bool isReversed = state.isReversed ^ next.ref().isReversed;

	m_current = state.name;
	m_elapsedTime = isReversed ? ANIMATION_FRAME : 0;
	m_animationNumber = next.ref().handle;
	m_isReversed = isReversed;
	m_isAnimating = true;
}

bool Field::isGround()
{
	return !(m_name.at(m_name.length() - 7) == 'k');
}
