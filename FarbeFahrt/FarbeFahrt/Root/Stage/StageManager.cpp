# include "StageManager.h"

# include "StageFactory.h"

# include "Actor/Field/Field.h"
# include "Actor/Gimmick/GimmickManager.h"

# include "World.h"

# include "Utility/SingletonFinalizer.h"
# include "Utility/StoryManager/StoryManager.h"
# include "Utility/BGM.h"

# include "Manager/EndManager.h"

# include "Experimental/AnimateState.h"

# include <fstream>

StageManager::StageManager()
	: m_current()
	, m_next()
{

}

void StageManager::initialize(const std::string& indexFilename)
{
	std::fstream stream { indexFilename };

	std::string currentDirectory = "";
	std::string buffer;

	std::string firstStageName;

	// ステージ一覧をロード
	while (std::getline(stream, buffer))
	{
		auto split = String::Split(buffer, ',');

		// カレントディレクトリの変更
		if (split[0] == "c")
		{
			currentDirectory = split[1];
			continue;
		}

		// ステージデータの読込
		if (split[0] == "s")
		{
			StageFactory().Load(currentDirectory + split[2], m_stageDatas[split[1]]);
		}

		// 最初のステージ指定
		if (split[0] == "f")
		{
			firstStageName = split[1];
		}
	}

	if (firstStageName == "")
	{
		firstStageName = m_stageDatas.begin()->first;
	}

	// 最初のステージ
	m_next.first = m_next.second = m_stageDatas.at(firstStageName);
	m_current.playerPosition = Vector3::Zero();
	m_current.endName = "";
	m_current.message = "Opening";
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
		world->findGroup(ActorTag::Goal)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.kill();
		});

		// 現在のフィールドに閉じるアニメーションをさせる
		/*world->findGroup(ActorTag::Field)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.sendMessage("CloseAnimate", nullptr);
		});*/
		world->findGroup(ActorTag::Field)->eachChildren(
			[] (BaseActor& actor)
		{
			AnimateState state { "Close", false };
			actor.sendMessage("Animate", &state);
		});
	}
	
	m_current = nextStage();
	world->apply(m_current, false);
	m_next.first = m_current.nextStage.first != "" ? m_stageDatas.at(m_current.nextStage.first) : StageData();
	m_next.second = m_current.nextStage.second != "" ? m_stageDatas.at(m_current.nextStage.second) : StageData();
	EndManager::SetShowStaffRoll(m_current.showStaffRoll);

	StoryManager::reset(BitFlag::GOAL);
	StoryManager::reset(BitFlag::NEXT);
	GimmickManager::reset();
}

void StageManager::apply(World* const world)
{
	world->apply(m_current, true);
	m_next.first = m_stageDatas.at(m_current.nextStage.first);
	m_next.second = m_stageDatas.at(m_current.nextStage.second);
}

std::string StageManager::endName() const
{
	return m_current.endName;
}

bool StageManager::isEnd() const
{
	std::string endname = m_current.endName;
	std::string filename = nextStage().filename;
	return !endname.empty() && filename.empty();
}

const StageData& StageManager::current() const
{
	return m_current;
}

const StageManager::Stages& StageManager::nextStages() const
{
	return m_next;
}

const std::string& StageManager::bgmName() const
{
	return m_current.bgmName;
}

const std::unordered_map<std::string, StageData>& StageManager::allStageData() const
{
	return m_stageDatas;
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
