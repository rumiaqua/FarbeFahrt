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

GameMain::GameMain()
	: m_stageManager()
{

}

void GameMain::loadContents(Loader& loader)
{
	m_loader = &loader;

	// 必ず読むリソース
	// とりあえずここにおいておく

	/*for (auto&& resource : m_stageManager.current().resourceList)
	{
		loader.loadContent(resource.first, resource.second);
	}*/

	loader.loadContent("BaseBook", "Model/本/新本.pmx");
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
	/*m_world->addActor(ActorTag::Effect, std::make_shared<Field>(
		*m_world, "book", Vector3(0.0f, -5.0f, 0.0f), 3.0f));*/
	m_world->addActor(ActorTag::Effect, std::make_shared<AnimateActor>(
		*m_world, "BaseBook", Vector3(0.0f, -5.0f, 0.0f), 3.0f));
	// 机
	m_world->addActor(ActorTag::Effect, std::make_shared<StaticObject>(
		*m_world, "desk", Vector3(-60.0f, -320.0f, 100.0f), (float)Math::ToRadian(-90.0), 0.8f));


	// m_stageManager.next(m_world.get());

	// 次のステージへすぐ飛べるよう特別にフラグをtrueにする
	m_stageManager.initialize("Resources/Script/Stage/index.csv", "PlainA");
	StoryManager::set(BitFlag::GOAL);

	EndManager::Clear();

	AnimateActor::AnimationInfo info;
	info.animationNumber = 0;
	info.animationTime = 180.0f;
	m_world->findActor("BaseBook")->sendMessage("Animate", &info);
}

void GameMain::update()
{
	if (m_stageManager.bgmName() != "")
	{
		BGM::play(m_stageManager.bgmName());
	}

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
	//		// endNum分だけ左シフトさせる
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

		if (m_stageManager.isEnd())
		{
			if (!EndManager::isEnd())
			{
			EndManager::Set(m_stageManager.endName());
			m_world->findGroup(ActorTag::Field)->sendMessage("ReverseOpenAnimate", nullptr);

				AnimateActor::AnimationInfo info;
				info.animationNumber = 0;
				info.animationTime = 180.0f;
				info.isReversed = true;
				m_world->findActor("BaseBook")->sendMessage("Animate", &info);
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
