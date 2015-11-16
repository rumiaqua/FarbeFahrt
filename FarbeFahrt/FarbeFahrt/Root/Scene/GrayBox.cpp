# include "GrayBox.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageDataBuilder.h"

# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"
#include "Utility/StoryManager/StoryManager.h"

# include "Utility/SingletonFinalizer.h"

GrayBox::GrayBox()
	// : m_stageManager("Resources/Stage/GrayBox/1-1.txt")
	: m_stageManager("Resources/Stage/ScriptFormatSample.txt")
{

}

void GrayBox::loadContents(Loader& loader)
{
	m_loader = &loader;

	for (auto&& resource : m_stageManager.current().resourceList)
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
}

void GrayBox::initialize()
{
	m_world = std::make_shared<World>();

	m_stageManager.apply(m_world.get());

	Debug::SetClear(true);
}

void GrayBox::update()
{
	m_world->update();

	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}
}

void GrayBox::draw(Renderer& render)
{
	m_world->draw(render);
}

void GrayBox::post()
{
	if (m_stageManager.isNext())
	{
		m_stageManager.next(m_world.get());
		for (auto&& resource : m_stageManager.current().resourceList)
		{
			m_loader->loadContent(resource.first.toNarrow(), resource.second.toNarrow());
		}
		m_loader->load();
	}
}

void GrayBox::cleanUp()
{

}

bool GrayBox::isSwallow() const
{
	return true;
}
