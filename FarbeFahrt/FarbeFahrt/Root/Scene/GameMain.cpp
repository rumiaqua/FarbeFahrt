# include "GameMain.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageDataBuilder.h"

# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
#include "Utility/StoryManager/StoryManager.h"

# include "Utility/SingletonFinalizer.h"

# include "Manager/EndManager.h"

GameMain::GameMain()
	: m_stageManager()
{
	StoryManager::initialize();
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
}

void GameMain::initialize()
{
	m_world = std::make_shared<World>();

	// m_stageManager.next(m_world.get());

	// 次のステージへすぐ飛べるよう特別にフラグをtrueにする
	m_stageManager.initialize("Resources/Stage/PlainA.txt");
	StoryManager::set(BitFlag::GOAL);

	Debug::SetClear(true);
}

void GameMain::update()
{
	m_world->update();

	if (Input::IsClicked(KEY_INPUT_RETURN))
	{

	}

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
	render.drawFont("Windows でコンピュータの世界が広がります。");
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
	if (m_stageManager.endNum() != -1)
	{
			EndManager::setPattern(m_stageManager.endNum());
			m_manager->changeScene(Scene::End, 60.0f);
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
}

void GameMain::cleanUp()
{

}

bool GameMain::isSwallow() const
{
	return true;
}
