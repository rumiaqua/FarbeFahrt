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

# include "Utility/BGM.h"

# include "Scene.h"

# include "Experimental/AnimateState.h"

GameMain::GameMain()
	: m_stageManager()
{

}

void GameMain::loadContents(Loader& loader)
{
	m_loader = &loader;

	// 必ず読むリソース
	// とりあえずここにおいておく
	loader.loadContent("desk", "Model/机/つくえ.mqo");

	loader.loadContent("TrueEnd", "Texture/end/true.png");
	loader.loadContent("Message", "Texture/end/message.png");
	loader.loadContent("Clear", "Texture/end/clear.png");
	loader.loadContent("staffRoll", "Texture/StaffRoll.png");
}

void GameMain::initialize()
{
	StoryManager::initialize();

	m_world = std::make_shared<World>();

	// 本
	m_world->addActor(ActorTag::Effect, std::make_shared<Field>(
		*m_world, "book", Vector3(0.0f, -5.0f, 0.0f), 3.0f, "Resources/Script/Animation/Book.txt"));
	// 机
	m_world->addActor(ActorTag::Effect, std::make_shared<StaticObject>(
		*m_world, "desk", Vector3(-60.0f, -320.0f, 100.0f), (float)Math::ToRadian(-90.0), 0.8f));


	// m_stageManager.next(m_world.get());

	// 次のステージへすぐ飛べるよう特別にフラグをtrueにする
	m_stageManager.initialize("Resources/Script/Stage/index.csv", "Lowles");
	StoryManager::set(BitFlag::GOAL);

	EndManager::Clear();

	AnimateState state { "Open", false };
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

	m_world->update();
}

void GameMain::draw(Renderer& render)
{
	/*Debug::Println(String::Create("Gimmick : ", StoryManager::get(BitFlag::GIMMICK) ? "true" : "false"));
	Debug::Println(String::Create("Goal : ", StoryManager::get(BitFlag::GOAL) ? "true" : "false"));
	Debug::Println(String::Create("Next : ", StoryManager::get(BitFlag::NEXT) ? "true" : "false"));
	Debug::Println("point:%d", GimmickManager::get());*/
	m_world->draw(render);
}

void GameMain::post()
{
	if (m_stageManager.isNext())
	{
		if (EndManager::CanEnd())
		{
			m_manager->changeScene(Scene::End, 60.0f);
			EndManager::SetEnd(false);
			return;
		}

		if (m_stageManager.isEnd())
		{
			if (!EndManager::isEnd())
			{
				EndManager::Set(m_stageManager.endName());
				AnimateState state { "Open", true };
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

		// 現在のステージのリソースを待機ロード
		for (auto&& resource : m_stageManager.current().resourceList)
		{
			m_loader->loadContent(resource.first, resource.second);
		}
		// m_loader->load();

		// 次のシーンのリソースを待機ロード
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

	// メッセージ処理が可能であればメッセージ処理を行なう
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
