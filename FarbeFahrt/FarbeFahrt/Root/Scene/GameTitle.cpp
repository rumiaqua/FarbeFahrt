#include "GameTitle.h"
#include <Windows.h>

# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "ISceneMediator.h"

GameTitle::GameTitle()
{
	Debug::ChangeFontSize(30);
}
void GameTitle::loadContents(Loader& loader)
{
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