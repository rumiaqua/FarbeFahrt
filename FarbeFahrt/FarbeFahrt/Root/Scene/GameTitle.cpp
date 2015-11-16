#include "GameTitle.h"
#include <Windows.h>
#include "Utility\Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "ISceneMediator.h"

GameTitle::GameTitle()
{
	Debug::ChangeFontSize(30);
}
void GameTitle::loadContents(Loader& loader)
{
	loader.loadContent("Player", "Model/MMD–‚“±Žo’íVer1.1/ƒKƒuƒŠƒGƒ‰.pmx");
	loader.loadContent("sky", "Model/skydome/’‹‚ÌŒŽ.x");
	loader.loadContent("field", "Model/terrain/terrain.mqo");
	loader.loadContent("bang", "SE/test.wav");
	loader.loadContent("kari", "Texture/‰¼‚è‚»[‚·.png");
	loader.loadContent("book", "Model/–{2/book.pmx");
}
void GameTitle::initialize(){
}
void GameTitle::update(){
	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->popScene();
	}
}
void GameTitle::draw(Renderer& render)
{
	NoUse(render);

	Debug::Println("‚½‚¢‚Æ‚é‚ª‚ß‚ñ‚¾‚æ");
}
void GameTitle::cleanUp(){
}
bool GameTitle::isSwallow() const
{
	return true;
}
GameTitle::~GameTitle()
{
}