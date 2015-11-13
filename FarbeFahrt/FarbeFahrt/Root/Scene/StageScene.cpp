# include "StageScene.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageBuilder.h"

# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"

StageScene::StageScene()
	: m_stageName("Resources/Stage/Sougen.txt")
{

}

void StageScene::loadContents(Loader& loader)
{
	// ���O
	m_factory.Load(m_stageName);

	// �X�e�[�W�X�N���v�g����K�v�ȃ��\�[�X���X�g���擾���ēǂݍ���
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}

	world->apply(m_factory.Data());
}

void StageScene::initialize()
{
	world = std::make_shared<World>();

	Debug::SetClear(true);
}

void StageScene::update()
{
	world->update();

	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}
	if (Input::IsClicked(KEY_INPUT_SPACE))
	{
		m_manager->changeScene(Scene::drawGameTitle);
	}
}

void StageScene::draw(Renderer& render)
{
	world->draw(render);
}

void StageScene::cleanUp()
{

}

bool StageScene::isSwallow() const
{
	return true;
}
