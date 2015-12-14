# include "Title.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Mouse.h"
# include "Utility/Renderer.h"

# include "ISceneMediator.h"
# include "Scene.h"

Title::Title()
{

}

void Title::loadContents(Loader& loader)
{
	loader.loadContent("Title", "Texture/title.png");
}

void Title::initialize()
{

}

void Title::update()
{
	if (Input::IsClicked(KEY_INPUT_RETURN) ||
		Mouse::IsClicked(MOUSE_INPUT_1))
	{
		m_manager->changeScene(Scene::Opening, 30.0f);
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
