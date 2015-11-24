# include "StageManager.h"

# include "StageFactory.h"

# include "Actor/Field/Field.h"

# include "World.h"

# include "Utility/SingletonFinalizer.h"
# include "Utility/StoryManager/StoryManager.h"

StageManager::StageManager(const String& firstStageName)
	: m_current()
	, m_next()
{
	// �_�~�[�f�[�^
	StageFactory().Load(firstStageName, m_next.first);
	StageFactory().Load(firstStageName, m_next.second);
	m_current.playerPosition = Vector3::Zero();
}

bool StageManager::isNext() const
{
	return StoryManager::get(BitFlag::GOAL);
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

		//// �V���ȃt�B�[���h��ǉ�����
		//for (auto&& field : nextStage().fieldList)
		//{
		//	// ����
		//	Actor actor = std::make_shared<Field>(
		//		*world, field.name, field.position, field.scale);
		//	// ���[���h�ɒǉ�
		//	world->addActor(ActorTag::Field, actor);
		//	// �J���A�j���[�V������������
		//	actor->sendMessage("OpenAnimate", nullptr);
		//}
	}
	StoryManager::reset(BitFlag::GIMMICK | BitFlag::GOAL);
	
	m_current = nextStage();
	world->apply(m_current, false);
	StageFactory().Load(m_current.nextStage.first, m_next.first);
	StageFactory().Load(m_current.nextStage.second, m_next.second);
}

void StageManager::apply(World* const world)
{
	world->apply(m_current, true);
	StageFactory().Load(m_current.nextStage.first, m_next.first);
	StageFactory().Load(m_current.nextStage.second, m_next.second);
	// world->findActor("PlayerSpawner")->sendMessage("PlayerSpawn", nullptr);
}

const StageData& StageManager::current() const
{
	return m_current;
}

bool StageManager::isFirst() const
{
	return StoryManager::get(BitFlag::GIMMICK);
}

const StageData& StageManager::nextStage() const
{
	return isFirst() ? m_next.first : m_next.second;
}
