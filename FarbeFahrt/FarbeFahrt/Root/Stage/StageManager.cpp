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
	, m_threshold(0)
{
}

void StageManager::initialize(const std::string& indexFilename)
{
	std::fstream stream { indexFilename };

	std::string currentDirectory = "";
	std::string buffer;

	std::string firstStageName;

	// �X�e�[�W�ꗗ�����[�h
	while (std::getline(stream, buffer))
	{
		auto split = String::Split(buffer, ',');

		// �J�����g�f�B���N�g���̕ύX
		if (split[0] == "c")
		{
			currentDirectory = split[1];
			continue;
		}

		// �X�e�[�W�f�[�^�̓Ǎ�
		if (split[0] == "s")
		{
			StageFactory().Load(currentDirectory + split[2], m_stageDatas[split[1]]);
		}

		// �ŏ��̃X�e�[�W�w��
		if (split[0] == "f")
		{
			firstStageName = split[1];
		}
	}

	if (firstStageName == "")
	{
		firstStageName = m_stageDatas.begin()->first;
	}

	// �ŏ��̃X�e�[�W
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
	// ���y�[�W�Ɉړ�
	{
		// �s�v�ȃI�u�W�F�N�g�̍폜
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
		world->findGroup(ActorTag::Effect)->eachChildren(
			[] (BaseActor& actor)
		{
			actor.kill();
		});

		AnimateState state { "Close", false };
		// ���݂̃t�B�[���h�ɕ���A�j���[�V������������
		world->findGroup(ActorTag::Field)->eachChildren(
			[&state] (BaseActor& actor)
		{
			actor.sendMessage("Animate", &state);
		});
	}
	
	// ���̃X�e�[�W���擾���ēK�p
	m_current = nextStage();
	world->apply(m_current, false);

	// ���̃X�e�[�W��ǂݍ���
	m_next.first = m_current.nextStage.first != "" ? m_stageDatas.at(m_current.nextStage.first) : StageData();
	m_next.second = m_current.nextStage.second != "" ? m_stageDatas.at(m_current.nextStage.second) : StageData();
	EndManager::SetShowStaffRoll(m_current.showStaffRoll);
	m_threshold = m_current.threshold;

	// �t���O�̃��Z�b�g
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

std::string StageManager::getThreshold() const
{
	return String::Create("Threshold : ", GimmickManager::get(), " / ", m_threshold);
}

bool StageManager::isFirst() const
{
	// bool first = StoryManager::get(BitFlag::GIMMICK);
	int numGimmick = GimmickManager::get();
	int threshold = m_threshold;
	return numGimmick >= threshold;
}

const StageData& StageManager::nextStage() const
{
	return isFirst() ? m_next.first : m_next.second;
}
