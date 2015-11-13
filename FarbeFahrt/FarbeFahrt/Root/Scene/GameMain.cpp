#include "GameMain.h"

#include "Actor/Player.h"
#include "Actor/Camera/Camera.h"
#include "Actor/SkyDome/Skydome.h"
#include "Actor/Field/Field.h"
#include "Actor/StaicObject.h"
#include "Actor/SkinObject.h"
#include "Actor/Gimmick/Gimmick.h"
#include "Actor/Goal/Goal.h"

#include "Utility/Debug.h"
#include "Utility/Loader.h"
#include "Utility/Renderer.h"

#include "ISceneMediator.h"

GameMain::GameMain()
{

}
void GameMain::loadContents(Loader& loader)
{
	loader.loadContent("Player", "Model/MMD魔導姉弟Ver1.1/ミハイル.pmx");
	loader.loadContent("sky", "Model/skydome/昼の月.x");
	loader.loadContent("field", "Model/terrain/terrain.mqo");
	loader.loadContent("bang", "SE/test.wav");
	loader.loadContent("kari", "Texture/仮りそーす.png");
	loader.loadContent("book", "Model/本2/book.pmx");
	loader.loadContent("test", "Model/MMD魔導姉弟Ver1.1/ガブリエラ.pmx");
}
void GameMain::initialize()
{
	world = std::make_shared<World>();
	world->addActor(ActorTag::Player, std::make_shared<Player>(*world, Vector3::Zero()));
	world->addCamera(std::make_shared<Camera>(*world));
	world->addField(std::make_shared<Field>(*world, "field", 0.5f));
	world->addSkydome(std::make_shared<Skydome>(*world, "sky"));

	//world->addActor(ActorTag::Enemy, std::make_shared<StaticObject>(*world,"book", Vector3(0,0,-30)));
	world->addActor(ActorTag::Goal, std::make_shared<Goal>(*world, "test", Vector3(0, -80, 150)));

	Debug::SetClear(true);
	Debug::ChangeFontSize(16);
}
void GameMain::update()
{
	world->update();

	// エンターでエディターシーンをプッシュする
	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}

	// スペースキーでタイトルシーンをプッシュする	
	if (Input::IsClicked(KEY_INPUT_SPACE))
	{
		m_manager->pushScene(Scene::drawGameTitle, 60.0f);
	}

	Debug::Println("%d",world->getFlag());
}
void GameMain::draw(Renderer& render)
{
	world->draw(render);
}

void GameMain::cleanUp()
{

}

bool GameMain::isSwallow() const
{
	return false;
}

GameMain::~GameMain()
{
}