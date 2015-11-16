# include "StageScene.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageBuilder.h"

# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"

# include "Utility/SingletonFinalizer.h"
# include "Experimental\FlagManager.h"

StageScene::StageScene()
{

}

void StageScene::loadContents(Loader& loader)
{
	// ���O
	m_factory.Load("Resources/Stage/Sougen.txt");
	// �X�e�[�W�X�N���v�g����K�v�ȃ��\�[�X���X�g���擾���ēǂݍ���
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
	// �K�p
	m_currentStageData = m_factory.Data();

	// ���O
	m_factory.Load("Resources/Stage/Mori.txt");
	// �X�e�[�W�X�N���v�g����K�v�ȃ��\�[�X���X�g���擾���ēǂݍ���
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
	// �K�p
	m_nextStageData1 = m_factory.Data();

	// ���O
	m_factory.Load("Resources/Stage/Mori2.txt");
	// �X�e�[�W�X�N���v�g����K�v�ȃ��\�[�X���X�g���擾���ēǂݍ���
	for (auto&& resource : m_factory.Resources())
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}
	// �K�p
	m_nextStageData2 = m_factory.Data();

	// ���[���h�ɓK�p
	world->apply(m_currentStageData, false);
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
	auto& instance = Singleton<FlagManager>::Instance();
	if (instance.Test(Flag::NextStage))
	{
		world->apply(instance.Test(Flag::Gimmick) ? m_nextStageData1 : m_nextStageData2, true);
		instance.Set(false);
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
