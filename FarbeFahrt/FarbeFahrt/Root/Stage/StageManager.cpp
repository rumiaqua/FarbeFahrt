# include "StageManager.h"

# include "StageFactory.h"

# include "Actor/Field/Field.h"

# include "World.h"

# include "Utility/SingletonFinalizer.h"
# include "Utility/StoryManager/StoryManager.h"

StageManager::StageManager(const std::string& firstStageName)
	: m_current()
	, m_next()
{
	// �_�~�[�f�[�^
	StageFactory().Load(firstStageName, m_next.first);
	StageFactory().Load(firstStageName, m_next.second);
	m_current.playerPosition = Vector3::Zero();
	m_current.endNum = -1;
}

bool StageManager::isNext() const
{
	bool next = StoryManager::get(BitFlag::GOAL);
	return next;
}

void StageManager::next(World* const world)
{	
	// m_current = nextStage();
	// apply(world);
	//world->findCamera()->sendMessage("toPlayerCamera", nullptr);
	// ���y�[�W�Ɉړ�
	{
		world->findGroup(ActorTag::Object)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.kill();
		});
		world->findGroup(ActorTag::Gimmick)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.kill();
		});
		world->findGroup(ActorTag::Player)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.kill();
		});

		// ���݂̃t�B�[���h�ɕ���A�j���[�V������������
		world->findGroup(ActorTag::Field)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.sendMessage("CloseAnimate", nullptr);
		});
	}
	
	m_current = nextStage();
	world->apply(m_current, false);
	StageFactory().Load(m_current.nextStage.first, m_next.first);
	StageFactory().Load(m_current.nextStage.second, m_next.second);

	StoryManager::reset(BitFlag::GOAL);
	StoryManager::reset(BitFlag::NEXT);
}

void StageManager::apply(World* const world)
{
	world->apply(m_current, true);
	StageFactory().Load(m_current.nextStage.first, m_next.first);
	StageFactory().Load(m_current.nextStage.second, m_next.second);
}

int StageManager::endNum() const
{
	return m_current.endNum;
}

const StageData& StageManager::current() const
{
	return m_current;
}

const StageManager::Stages& StageManager::nextStages() const
{
	return m_next;
}

bool StageManager::isFirst() const
{
	bool first = StoryManager::get(BitFlag::GIMMICK);
	return first;
}

const StageData& StageManager::nextStage() const
{
	return isFirst() ? m_next.first : m_next.second;
}
