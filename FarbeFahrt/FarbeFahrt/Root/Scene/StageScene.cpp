# include "StageScene.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageBuilder.h"

# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"
#include "Utility/StoryManager/StoryManager.h"

# include "Utility/SingletonFinalizer.h"

StageScene::StageScene()
{

}

void StageScene::loadContents(Loader& loader)
{
	// 名前
	m_factory.Load("Resources/Stage/TestMap.txt");
	// ステージスクリプトから必要なリソースリストを取得して読み込む
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
	// 適用
	m_currentStageData = m_factory.Data();

	// 名前
	m_factory.Load("Resources/Stage/Mori.txt");
	// ステージスクリプトから必要なリソースリストを取得して読み込む
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
	// 適用
	m_nextStageData1 = m_factory.Data();

	// 名前
	m_factory.Load("Resources/Stage/Mori2.txt");
	// ステージスクリプトから必要なリソースリストを取得して読み込む
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
	// 適用
	m_nextStageData2 = m_factory.Data();

	// ワールドに適用
	world->apply(m_currentStageData, false);
}

void StageScene::initialize()
{
	world = std::make_shared<World>();

	Debug::SetClear(true);
}

void StageScene::update()
{
	world->update();

	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}
	if (Input::IsClicked(KEY_INPUT_SPACE))
	{
		m_manager->changeScene(Scene::drawGameTitle);
	}

	if (world->getFlag(BitFlag::GOAL))
	{
		world->apply(world->getFlag(BitFlag::GIMMICK) ? m_nextStageData1 : m_nextStageData2, true);
		world->initFlag();
	}
}

void StageScene::draw(Renderer& render)
{
	world->draw(render);
}

void StageScene::cleanUp()
{

}

bool StageScene::isSwallow() const
{
	return true;
}
