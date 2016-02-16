# include "GameMain.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"
# include "Utility/StoryManager/StoryManager.h"
# include "Utility/SingletonFinalizer.h"
# include "Utility/Math.h"

# include "Stage/ScriptStageDataBuilder.h"

# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
# include "Actor/Gimmick/GimmickManager.h"
# include "Actor/Field/Field.h"
# include "Actor/StaticObject.h"
# include "Actor/AnimateActor.h"

# include "Manager/EndManager.h"
# include "Manager/MessageManager.h"
# include "Manager/BackLogManager.h"

# include "Utility/BGM.h"
# include "Utility/Renderer.h"
# include "Utility/Mouse.h"

# include "Scene.h"

# include "Experimental/AnimateState.h"

# include "Scene\ISceneMediator.h"

# include "Actor/Accessory.h"

GameMain::GameMain()
	: m_stageManager()
{

}

void GameMain::loadContents(Loader& loader)
{
	m_loader = &loader;

	// �K���ǂރ��\�[�X
	// �Ƃ肠���������ɂ����Ă���
	loader.loadContent("desk", "Model/��/����.mqo");

	loader.loadContent("end1", "Texture/end/end1.png");
	loader.loadContent("end2", "Texture/end/end2.png");

	loader.loadContent("Message", "Texture/end/message.png");
	loader.loadContent("staffRoll", "Texture/StaffRoll.png");
	loader.loadContent("Player", "Model/MMD�����o��Ver1.1/�~�n�C��.pmx");
	loader.loadContent("LightParticle", "Texture/Particle.png");	

	loader.loadContent("TitleChooseBack", "Texture/TitleChoose/Back.png");
	loader.loadContent("YesOutMouse", "Texture/TitleChoose/yes.png");
	loader.loadContent("YesOnMouse", "Texture/TitleChoose/yes_2.png");
	loader.loadContent("NoOutMouse", "Texture/TitleChoose/no.png");
	loader.loadContent("NoOnMouse", "Texture/TitleChoose/no_2.png");

	loader.loadContent("HerbAccessory", "Model/3D/����r����/����r����.mqo");
	loader.loadContent("MedicineAccessory", "Model/3D/��/��.mqo");
	loader.loadContent("ElderAccessory", "Model/3D/�������r/���r.mqo");
}

void GameMain::initialize()
{
	StoryManager::initialize();

	m_world = std::make_shared<World>(m_manager);

	// �{
	m_world->addActor(ActorTag::Environment, std::make_shared<Field>(
		*m_world, "book", Vector3(0.0f, -5.0f, 0.0f), 3.0f, "Resources/Script/Animation/Book.txt"));
	// ��
	m_world->addActor(ActorTag::Environment, std::make_shared<StaticObject>(
		*m_world, "desk", Vector3(-60.0f, -330.0f, 100.0f), (float)Math::ToRadian(-90.0), 0.8f));

	// �A�N�Z�T���[
	m_world->addActor(ActorTag::Environment, std::make_shared<Accessory>(*m_world));

	// ���̃X�e�[�W�ւ�����ׂ�悤���ʂɃt���O��true�ɂ���
	m_stageManager.initialize("Resources/Script/Stage/index.csv");
	StoryManager::set(BitFlag::GOAL);

	// �G���h�̏�����
	EndManager::Clear();

	AnimateState state{ "Start", false };
	if (auto book = m_world->findActor("book"))
	{
		book->sendMessage("Animate", &state);
	}
}

void GameMain::update()
{
	if (m_stageManager.bgmName() != "")
	{
		BGM::play(m_stageManager.bgmName());
	}

	if (Mouse::IsClicked(MOUSE_INPUT_RIGHT))
	{
		m_manager->pushScene(Scene::BackLog);
	}

	if (Input::IsClicked(KEY_INPUT_ESCAPE))
	{
		m_manager->pushScene(Scene::TitleChoose);
	}

	m_world->update();
}

void GameMain::draw(Renderer& renderer)
{
	/*Debug::Println(String::Create("Gimmick : ", StoryManager::get(BitFlag::GIMMICK) ? "true" : "false"));
	Debug::Println(String::Create("Goal : ", StoryManager::get(BitFlag::GOAL) ? "true" : "false"));
	Debug::Println(String::Create("Next : ", StoryManager::get(BitFlag::NEXT) ? "true" : "false"));
	Debug::Println("point:%d", GimmickManager::get());*/

	m_world->draw(renderer);

	// �M�~�b�N�N���� / �M�~�b�N臒l
	Debug::Println(String::Create("Gimmick : ", GimmickManager::get(), " / ", GimmickManager::getMax()));

	if (Input::IsPressed(KEY_INPUT_N))
	{
		renderer.ChangeNight();
	}
	if (Input::IsPressed(KEY_INPUT_M))
	{
		renderer.ChangeDay();
	}
}

void GameMain::post()
{
	// ���X�e�[�W�����݂���ꍇ
	if (m_stageManager.isNext())
	{
		// �G���h�V�[���ւ̑J�ڂ��\�ł���ΑJ��
		if (EndManager::CanEnd())
		{
			m_manager->changeScene(Scene::End, 60.0f);
			EndManager::SetEnd(false);
			return;
		}

		// �I���X�e�[�W�������ꍇ
		if (m_stageManager.isEnd())
		{
			// �G���h�V�[�����Z�b�g����Ă���ꍇ
			if (!EndManager::isEnd())
			{
				EndManager::Set(m_stageManager.endName());
				// �t�B�[���h�Ɩ{�̃G���h�A�j���[�V�������Đ�����
				AnimateState state { "End", false };
				m_world->findGroup(ActorTag::Field)->sendMessage("Animate", &state);
				if (auto book = m_world->findActor("book"))
				{
					book->sendMessage("Animate", &state);
				}
			}
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
