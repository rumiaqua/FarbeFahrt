# include "Opening.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"
#include "Utility/StoryManager/StoryManager.h"
# include "Utility/SingletonFinalizer.h"
# include "Utility/Math.h"

# include "Stage/ScriptStageDataBuilder.h"
# include "ISceneMediator.h"

# include "Actor/Camera/Camera.h"
#include "Actor/Gimmick/GimmickManager.h"
# include "Actor/Field/Field.h"
# include "Actor/StaticObject.h"

# include "Manager/EndManager.h"
# include "Manager/MessageManager.h"
# include "Manager/BackLogManager.h"

# include "Scene.h"

Opening::Opening()
	: m_isOnce(false)
{

}

void Opening::loadContents(Loader& loader)
{
	loader.loadContent("book", "Model/本/新本.pmx");
	loader.loadContent("desk", "Model/机/つくえ.mqo");
}

void Opening::initialize()
{
	StoryManager::initialize();

	m_world = std::make_shared<World>();

	// 本
	m_world->addActor(ActorTag::Effect, std::make_shared<Field>(
		*m_world, "book", Vector3(0.0f, -5.0f, 0.0f), 3.0f, "Resources/Script/Animation/Default.txt"));
	// 机
	m_world->addActor(ActorTag::Effect, std::make_shared<StaticObject>(
		*m_world, "desk", Vector3(-60.0f, -320.0f, 100.0f), (float)Math::ToRadian(-90.0), 0.8f));

	MessageManager::Add("Opening");

	m_isOnce = false;

	// バックログの初期化
	BackLogManager::Clear();
}

void Opening::update()
{
	m_world->update();
	if (!m_isOnce)
	{
		m_isOnce = true;
		m_manager->pushScene(Scene::Message);
		return;
	}
	m_manager->changeScene(Scene::GameMain);
}

void Opening::draw(Renderer& renderer)
{
	m_world->draw(renderer);
}

void Opening::post()
{

}

void Opening::cleanUp()
{

}

bool Opening::isSwallow() const
{
	return true;
}
