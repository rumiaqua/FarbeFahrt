# include "Opening.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Stage/ScriptStageDataBuilder.h"
# include "ISceneMediator.h"
# include "Actor/Camera/Camera.h"
#include "Utility/StoryManager/StoryManager.h"
#include "Actor/Gimmick/GimmickManager.h"
# include "Utility/SingletonFinalizer.h"
# include "Manager/EndManager.h"
# include "Manager/MessageManager.h"
# include "Actor/Field/Field.h"
# include "Actor/StaticObject.h"
# include "Utility/Math.h"

# include "Scene.h"

Opening::Opening()
	: m_isOnce(false)
{

}

void Opening::loadContents(Loader& loader)
{
	loader.loadContent("book", "Model/ñ{/êVñ{.pmx");
	loader.loadContent("desk", "Model/ä˜/Ç¬Ç≠Ç¶.mqo");

	loader.loadContent("Player", "Model/MMDñÇì±éoíÌVer1.1/É~ÉnÉCÉã.pmx");
	loader.loadContent("Goal", "Model/ïΩå¥/Ç≠Ç≥.pmx");

	loader.loadContent("plainGround", "Stage/ïΩå¥/ïΩå¥ínñ /ïΩå¥ínñ .pmx");
	loader.loadContent("plainBackground", "Stage/ïΩå¥/ïΩå¥îwåi/ïΩå¥îwåi.pmx");

	loader.loadContent("flower1G", "Model/Gimmick/bookmark.mqo");
	loader.loadContent("flower1", "Model/Gimmick/ForestA/flower.mqo");
	loader.loadContent("flower2G", "Model/Gimmick/bookmark.mqo");
	loader.loadContent("flower2", "Model/Gimmick/ForestA/flower.mqo");

	loader.loadContent("nuts1G", "Model/Gimmick/bookmark.mqo");
	loader.loadContent("nuts1", "Model/Gimmick/ForestA/nuts1.mqo");
	loader.loadContent("nuts2G", "Model/Gimmick/bookmark.mqo");
	loader.loadContent("nuts2", "Model/Gimmick/ForestA/nuts2.mqo");

	loader.loadContent("forestGround", "Stage/êX/êXínñ /êXínñ .pmx");
	loader.loadContent("forestBackground", "Stage/êX/êXîwåi/êXîwåi.pmx");
}

void Opening::initialize()
{
	StoryManager::initialize();

	m_world = std::make_shared<World>();

	// ñ{
	m_world->addActor(ActorTag::Effect, std::make_shared<Field>(
		*m_world, "book", Vector3(0.0f, -5.0f, 0.0f), 3.0f));
	// ä˜
	m_world->addActor(ActorTag::Effect, std::make_shared<StaticObject>(
		*m_world, "desk", Vector3(-60.0f, -320.0f, 100.0f), (float)Math::ToRadian(-90.0), 0.8f));

	MessageManager::Add("Opening");

	m_isOnce = false;
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

void Opening::draw(Renderer& render)
{
	m_world->draw(render);
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
