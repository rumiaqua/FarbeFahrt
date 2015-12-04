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
	: m_endNum()
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

	loader.loadContent("bad", "Texture/end/bad.png");
	loader.loadContent("clear", "Texture/end/clear.png");
	loader.loadContent("true", "Texture/end/true.png");

	int num = (int)EndManager::getPattern() - 1;
	
	if (num < 0)
	{
		num = 0;
	}

	m_endNum = num;
}

void End::initialize()
{

}

void End::update()
{
	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->changeScene(Scene::StaffRoll, 60.0f);
	}
}

void End::draw(Renderer& renderer)
{
	static const std::string endResourceNames[] =
	{
		"bad",
		"clear",
		"bad",
		"true",
		"clear",
	};
	renderer.drawTexture(endResourceNames[m_endNum], Renderer::AspectType::LetterBox, Vector2(0, 0), Vector2(0.5f, 0.5f));
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
