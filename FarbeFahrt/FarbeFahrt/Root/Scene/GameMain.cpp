#include "GameMain.h"

#include "Actor/Player.h"
#include "Actor/Camera/Camera.h"
#include "Actor/SkyDome/Skydome.h"
#include "Actor/Field/Field.h"

#include "Utility/Debug.h"
# include "Utility/Loader.h"
# include "Utility/Renderer.h"

# include "ISceneMediator.h"

GameMain::GameMain()
{
}
void GameMain::loadContents(Loader& loader)
{
	loader.loadContent("Player", "Model/MMD�����o��Ver1.1/�K�u���G��.pmx");
	loader.loadContent("sky", "Model/skydome/���̌�.x");
	loader.loadContent("field", "Model/terrain/terrain.mqo");
	loader.loadContent("bang", "SE/test.wav");
	loader.loadContent("kari", "Texture/���肻�[��.png");

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

	// �G���^�[�ŃG�f�B�^�[�V�[�����v�b�V������
	if (Input::isClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}

	// �X�y�[�X�L�[�Ń^�C�g���V�[�����v�b�V������	
	if (Input::isClicked(KEY_INPUT_SPACE))
	{
		m_manager->pushScene(Scene::drawGameTitle, 60.0f);
	}
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