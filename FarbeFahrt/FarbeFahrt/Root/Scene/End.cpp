# include "End.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/StoryManager/StoryManager.h"
# include "Utility/Input.h"
# include "Utility/HandleList.h"
# include "Utility/SingletonFinalizer.h"

# include "Manager/EndManager.h"

# include "Scene/ISceneMediator.h"

End::End()
{

}

void End::loadContents(Loader& loader)
{
	std::string endResources[] =
	{
		"Texture/end/bad.png",
		"Texture/end/clear.png",
		"Texture/end/bad.png",
		"Texture/end/true.png",
		"Texture/end/clear.png",
	};

	int num = (int)EndManager::getPattern() - 1;

	if (num < 0)
	{
		num = 0;
	}

	loader.loadContent("end", endResources[num]);
}

void End::initialize()
{

}

void End::update()
{
	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->changeScene(Scene::GrayBox);
	}
}

void End::draw(Renderer& renderer)
{
	renderer.drawTexture("end", Renderer::AspectType::Expand);
}

void End::post()
{

}

void End::cleanUp()
{

}

bool End::isSwallow() const
{
	return true;
}
