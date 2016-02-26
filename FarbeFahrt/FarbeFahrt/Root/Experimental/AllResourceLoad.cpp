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
	loader.loadContent("book", "Model/Book/Book.pmx");
	loader.loadContent("desk", "Model/Š÷/‚Â‚­‚¦.mqo");

	loader.loadContent("TrueEnd", "Texture/end/true.png");
	loader.loadContent("Message", "Texture/end/message.png");
	loader.loadContent("Clear", "Texture/end/clear.png");
	loader.loadContent("staffRoll", "Texture/StaffRoll.png");
	loader.loadContent("Player", "Model/MMD–‚“±Žo’íVer1.1/ƒ~ƒnƒCƒ‹.pmx");

	loader.loadContent("curtain", "Texture/curtain.png");

	StageManager manager;
	manager.initialize("Resources/Script/Stage/index.csv");
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

void AllResourceLoad::draw(Renderer & renderer)
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
