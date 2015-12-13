# include "GameMain.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageDataBuilder.h"
# include "ISceneMediator.h"
# include "Actor/Camera/Camera.h"
#include "Utility/StoryManager/StoryManager.h"
#include "Actor/Gimmick/GimmickManager.h"
# include "Utility/SingletonFinalizer.h"
# include "Manager/EndManager.h"
# include "Manager/MessageManager.h"
# include "Actor/Field/Field.h"


GameMain::GameMain()
	: m_stageManager()
{
	StoryManager::initialize();
}

void GameMain::loadContents(Loader& loader)
{
	m_loader = &loader;

	// �K���ǂރ��\�[�X
	// �Ƃ肠���������ɂ����Ă���

	/*for (auto&& resource : m_stageManager.current().resourceList)
	{
		loader.loadContent(resource.first, resource.second);
	}*/

	loader.loadContent("book", "Model/�{/�V�{.pmx");
}

void GameMain::initialize()
{
	m_world = std::make_shared<World>();

	// �{
	m_world->addActor(ActorTag::Effect, std::make_shared<Field>(
		*m_world, "book", Vector3(0.0f, -5.0f, 0.0f), 3.0f));

	// m_stageManager.next(m_world.get());

	// ���̃X�e�[�W�ւ�����ׂ�悤���ʂɃt���O��true�ɂ���
	m_stageManager.initialize("Resources/Script/Stage/index.csv", "PlainA");
	MessageManager::Initialize("Resources/Script/Message/index.csv");
	StoryManager::set(BitFlag::GOAL);

	m_world->findActor("book")->sendMessage("OpenAnimate", nullptr);
}

void GameMain::update()
{
	m_world->update();

	/*if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}*/

}

void GameMain::draw(Renderer& render)
{
	Debug::Println(String::Create("Gimmick : ", StoryManager::get(BitFlag::GIMMICK) ? "true" : "false"));
	Debug::Println(String::Create("Goal : ", StoryManager::get(BitFlag::GOAL) ? "true" : "false"));
	Debug::Println(String::Create("Next : ", StoryManager::get(BitFlag::NEXT) ? "true" : "false"));
	Debug::Println("point:%d", GimmickManager::get());
	m_world->draw(render);
}

void GameMain::post()
{
	//# define NONE -1
	//	int endNum = m_stageManager.endNum();
	//	if (endNum != NONE)
	//	{
	//		return;
	//		// endNum���������V�t�g������
	//		StoryManager::set(BitFlag::BADEND << endNum);
	//		m_manager->changeScene(Scene::End, true);
	//		return;
	//	}
	//# undef NONE

	if (m_stageManager.isNext())
	{
		if (EndManager::CanEnd())
		{
			m_manager->changeScene(Scene::End, 60.0f);
			EndManager::SetEnd(false);
			return;
		}

		if (!m_stageManager.endName().empty())
		{
			EndManager::Set(m_stageManager.endName());
			m_world->findGroup(ActorTag::Field)->sendMessage("ReverseOpenAnimate", nullptr);
			m_world->findActor("book")->sendMessage("ReverseOpenAnimate", nullptr);
			return;
		}

		m_loader->cleanUp();

		m_stageManager.next(m_world.get());
		StoryManager::reset(BitFlag::GIMMICK | BitFlag::GOAL);

		// ���݂̃X�e�[�W�̃��\�[�X��ҋ@���[�h
		for (auto&& resource : m_stageManager.current().resourceList)
		{
			m_loader->loadContent(resource.first, resource.second);
		}
		// m_loader->load();

		// ���̃V�[���̃��\�[�X��ҋ@���[�h
		const auto& nexts = m_stageManager.nextStages();
		for (auto&& resource : nexts.first.resourceList)
		{
			m_loader->loadContent(resource.first, resource.second);
		}
		for (auto&& resource : nexts.second.resourceList)
		{
			m_loader->loadContent(resource.first, resource.second);
		}
		m_loader->load();
	}

	// ���b�Z�[�W�������\�ł���΃��b�Z�[�W�������s�Ȃ�
	if (MessageManager::CanShow())
	{
		m_manager->pushScene(Scene::Message);
	}
}

void GameMain::cleanUp()
{

}

bool GameMain::isSwallow() const
{
	return true;
}
