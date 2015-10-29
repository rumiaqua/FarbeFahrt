# include "StageScene.h"

# include "Utility/Loader.h"

StageScene::StageScene()
{
	m_factory.Load("Resources/Stage/Sougen.txt");
}

void StageScene::loadContents(Loader& loader)
{
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
}

void StageScene::initialize()
{
	world = std::make_shared<World>();
	m_factory.Apply(*world);
}

void StageScene::update()
{
	world->update();
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
