# include "Title.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Mouse.h"
# include "Utility/Renderer.h"
# include "Utility/BGM.h"

# include "Experimental/OneShotStage.h"

# include "ISceneMediator.h"
# include "Scene.h"

Title::Title()
{

}

void Title::loadContents(Loader& loader)
{
	loader.loadContent("Title", "Texture/title.png");
	loader.loadContent("TitleBGM", "Sound/BGM/Title.mp3");
}

void Title::initialize()
{
	
}

void Title::update()
{
	BGM::play("TitleBGM");
	
	if (Input::IsClicked(KEY_INPUT_RETURN) ||
		Mouse::IsClicked(MOUSE_INPUT_1))
	{
		m_manager->changeScene(Scene::Opening, 30.0f);
	}

	if (Input::IsClicked(KEY_INPUT_F1))
	{
		m_manager->changeScene(Scene::OneShotLauncher, 30.0f);
	}
}

void Title::draw(Renderer& render)
{
	render.drawTexture("Title", Renderer::AspectType::LetterBox);
}

void Title::post()
{

}

void Title::cleanUp()
{

}

bool Title::isSwallow() const
{
	return true;
}
