# include "End.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/StoryManager/StoryManager.h"
# include "Utility/Input.h"
# include "Utility/HandleList.h"
# include "Utility/SingletonFinalizer.h"

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
		"Texture/end/true.png",
	};

	int num =
		StoryManager::get(BitFlag::BADEND) ? 0 :
		StoryManager::get(BitFlag::CLEAR) ? 1 :
		2;

	// loader.loadContent("end", endResources[num]);
	loader.loadContent("end", "Texture/end/bad.png");
}

void End::initialize()
{

}

void End::update()
{
	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->changeScene(Scene::ObjectViewer);
	}
}

void End::draw(Renderer& renderer)
{
	int handle = Singleton<HandleList>::Instance().getHandle("end");
	DrawRotaGraph3(0, 0, 0, 0, 1.0, 1.0, 0.0, handle, TRUE);
	// renderer.drawTexture("end", 0, 0);
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
