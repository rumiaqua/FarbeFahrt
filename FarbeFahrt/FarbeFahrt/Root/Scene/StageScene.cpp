# include "StageScene.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/ScriptStageBuilder.h"
# include "Utility/Debug.h"

# include "ISceneMediator.h"

StageScene::StageScene()
{
	m_factory.Load("Resources/Stage/Sougen.txt");
}

void StageScene::loadContents(Loader& loader)
{
	auto& panda = m_factory.Resources();
	for (auto&& resource : panda)
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
}

void StageScene::initialize()
{
	world = std::make_shared<World>();
	m_factory.Apply(*world);
	Debug::SetClear(true);
}

void StageScene::update()
{
	world->update();

	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}

	// Save Action
	/*if (Input::isClicked(KEY_INPUT_1))
	{
		ScriptStageBuilder builder;
		builder.save("Resources/Stage/Sougen1.txt", world->getData());
	}*/
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
