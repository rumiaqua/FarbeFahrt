# include "GrayBox.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageDataBuilder.h"

# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"
#include "Utility/StoryManager/StoryManager.h"

# include "Utility/SingletonFinalizer.h"

GrayBox::GrayBox()
	: m_stageManager("Resources/Stage/PlainA.txt")
{

}

void GrayBox::loadContents(Loader& loader)
{
	m_loader = &loader;

	// �K���ǂރ��\�[�X
	// �Ƃ肠���������ɂ����Ă���
	loader.loadContent("sky", "Model/skydome/���̌�.x");

	/*for (auto&& resource : m_stageManager.current().resourceList)
	{
		loader.loadContent(resource.first.toNarrow(), resource.second.toNarrow());
	}*/
}

void GrayBox::initialize()
{
	m_world = std::make_shared<World>();

	// m_stageManager.next(m_world.get());

	// ���̃X�e�[�W�ւ�����ׂ�悤���ʂɃt���O��true�ɂ���
	StoryManager::set(BitFlag::GOAL);

	Debug::SetClear(true);
}

void GrayBox::update()
{
	m_world->update();

	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->pushScene(Scene::Editor);
	}
}

void GrayBox::draw(Renderer& render)
{
	m_world->draw(render);
}

void GrayBox::post()
{
	/*if (m_stageManager.isNext())
	{
		m_stageManager.next(m_world.get());

		for (auto&& resource : m_stageManager.current().resourceList)
		{
			m_loader->loadContent(resource.first.toNarrow(), resource.second.toNarrow());
		}

		m_loader->loadASync();
	}*/

	if (m_stageManager.isNext())
	{
		m_stageManager.next(m_world.get());

		// ���݂̃X�e�[�W�̃��\�[�X��ҋ@���[�h
		for (auto&& resource : m_stageManager.current().resourceList)
		{
			m_loader->loadContent(resource.first.toNarrow(), resource.second.toNarrow());
		}
		m_loader->load();

		// ���̃V�[���̃��\�[�X���ҋ@���[�h
		const auto& nexts = m_stageManager.nextStages();
		for (auto&& resource : nexts.first.resourceList)
		{
			m_loader->loadContent(resource.first.toNarrow(), resource.second.toNarrow());
		}
		for (auto&& resource : nexts.second.resourceList)
		{
			m_loader->loadContent(resource.first.toNarrow(), resource.second.toNarrow());
		}
		m_loader->loadASync();
	}
}

void GrayBox::cleanUp()
{

}

bool GrayBox::isSwallow() const
{
	return true;
}
