# include "AllResourceLoad.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"

# include "Scene/ISceneMediator.h"
# include "Scene/Scene.h"

# include "Stage/StageManager.h"

AllResourceLoad::AllResourceLoad()
{

}

void AllResourceLoad::loadContents(Loader& loader)
{
	loader.loadContent("desk", "Model/Š÷/‚Â‚­‚¦.mqo");

	loader.loadContent("TrueEnd", "Texture/end/true.png");
	loader.loadContent("Message", "Texture/end/message.png");
	loader.loadContent("Clear", "Texture/end/clear.png");
	loader.loadContent("staffRoll", "Texture/StaffRoll.png");

	StageManager manager;
	manager.initialize("Resources/Script/Stage/index.csv", "PlainA");
	for (auto&& data : manager.allStageData())
	{
		for (auto&& resource : data.second.resourceList)
		{
			loader.loadContent(resource.first, resource.second);
		}
	}
}

void AllResourceLoad::initialize()
{
}

void AllResourceLoad::update()
{
	m_manager->popScene();
}

void AllResourceLoad::draw(Renderer & render)
{

}

void AllResourceLoad::post()
{
}

void AllResourceLoad::cleanUp()
{
}

bool AllResourceLoad::isSwallow() const
{
	return true;
}
