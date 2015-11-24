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
	// ダミーデータ
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
	// 次ページに移動
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

		// 現在のフィールドに閉じるアニメーションをさせる
		world->findGroup(ActorTag::Field)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.sendMessage("CloseAnimate", nullptr);
		});

		//// 新たなフィールドを追加する
		//for (auto&& field : nextStage().fieldList)
		//{
		//	// 生成
		//	Actor actor = std::make_shared<Field>(
		//		*world, field.name, field.position, field.scale);
		//	// ワールドに追加
		//	world->addActor(ActorTag::Field, actor);
		//	// 開くアニメーションをさせる
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
