#include "Prologue.h"
#include "Utility/Loader.h"
#include "Utility\Renderer.h"

#include "Utility\Debug.h"
#include "Utility\String.h"
# include "ISceneMediator.h"
# include "Scene.h"
#include "Utility\Mouse.h"
Prologue::Prologue()
	:m_timer(0), m_texNum(0)
{
	textures = {"page1","page2","page3" };

}

void Prologue::loadContents(Loader& loader)
{
	loader.loadContent("page0", "Texture/demo0.png");
	loader.loadContent("page1", "Texture/demo1.png");
	loader.loadContent("page2", "Texture/demo2.png");
	loader.loadContent("page3", "Texture/demo3.png");
}

void Prologue::initialize()
{
}

void Prologue::update()
{
	++m_timer;
	if (m_timer == 1198)
	{
		m_manager->changeScene(Scene::Title, 60.0f);
	}
	m_texNum = (int)(m_timer / 400);
	Debug::Println(String::Create(m_texNum));

	if (Mouse::IsClicked(MOUSE_INPUT_1))
	{
		m_manager->changeScene(Scene::Title, 60.0f);
	}
}

void Prologue::draw(Renderer& renderer)
{
	renderer.drawTexture("page0", Renderer::AspectType::LetterBox);
	renderer.drawTexture(textures[m_texNum], Renderer::AspectType::LetterBox);
}

void Prologue::post()
{

}

void Prologue::cleanUp()
{
	m_timer = 0;
	m_texNum = 0;
}

bool Prologue::isSwallow() const
{
	return true;
}
