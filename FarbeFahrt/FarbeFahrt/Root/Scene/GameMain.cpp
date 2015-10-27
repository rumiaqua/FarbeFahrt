#include "GameMain.h"
#include "Utility/Renderer.h"
#include "Actor/Player.h"
#include "Actor/Camera/Camera.h"
#include "Actor/SkyDome/Skydome.h"
#include "Actor/Field/Field.h"
#include "Utility/Debug.h"

# include "SceneManager.h"

GameMain::GameMain()
{
}
void GameMain::loadContents(Loader& loader)
{
	loader.loadContent("Player", "Model/MMD–‚“±o’íVer1.1/ƒKƒuƒŠƒGƒ‰.pmx");
	loader.loadContent("sky", "Model/skydome/’‹‚ÌŒ.x");
	loader.loadContent("field", "Model/terrain/terrain.mqo");
	loader.loadContent("bang", "SE/test.wav");
	loader.loadContent("kari", "Texture/‰¼‚è‚»[‚·.png");

}
void GameMain::initialize()
{
	world = std::make_shared<World>();
	world->addActor(ActorTag::Player, std::make_shared<Player>(*world, Vector3::zero()));
	world->addCamera(std::make_shared<Camera>(*world));
	world->addField(std::make_shared<Field>(*world));
	world->addSkydome(std::make_shared<Skydome>(*world));

	Debug::setClear(true);
	Debug::changeFontSize(16);
}
void GameMain::update()
{
	world->update();

	if (Input::isClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::drawGameTitle);
	}
}
void GameMain::draw(Renderer& render)
{
	world->draw(render);
}

void GameMain::cleanUp()
{

}

GameMain::~GameMain()
{
}