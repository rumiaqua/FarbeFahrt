#include "GameMain.h"
#include "Utility/Renderer.h"
#include "Actor/Player.h"
#include "Actor/Camera/Camera.h"
#include "Actor/SkyDome/Skydome.h"
#include "Actor/Field/Field.h"
#include "Utility/Debug.h"

GameMain::GameMain()
{
}
void GameMain::loadContents(Loader& loader)
{
	loader.loadModel("Player", "Resources/Model/MMD–‚“±Žo’íVer1.1/ƒKƒuƒŠƒGƒ‰.pmx");
	loader.loadModel("sky", "Resources/Model/skydome/’‹‚ÌŒŽ.x");
	loader.loadModel("field", "Resources/Model/terrain/terrain.mqo");
	loader.loadTexture("test", "Resources/terrain/’n–Ê.jpg");
	loader.loadSE("bang", "Resources/SE/test.wav");
}
void GameMain::initialize()
{
	world = std::make_shared<World>();
	world->addActor(ActorTag::Player, std::make_shared<Player>(*world, VGet(0.0f, 0.0f, 0.0f)));
	world->addCamera(std::make_shared<Camera>(*world));
	world->addField(std::make_shared<Field>(*world));
	world->addSkydome(std::make_shared<Skydome>(*world));

	Debug::setClear(true);
}
void GameMain::update()
{
	world->update();
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