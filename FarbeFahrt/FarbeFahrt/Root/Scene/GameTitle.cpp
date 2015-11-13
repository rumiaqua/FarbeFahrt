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
	loader.loadContent("Player", "Model/MMD魔導姉弟Ver1.1/ミハイル.pmx");
	loader.loadContent("sky", "Model/skydome/昼の月.x");
	loader.loadContent("field", "Model/terrain/terrain.mqo");
	loader.loadContent("bang", "SE/test.wav");
	loader.loadContent("kari", "Texture/仮りそーす.png");
	loader.loadContent("book", "Model/本2/book.pmx");
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
	Debug::Println("たいとるがめんだよ");
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