# include "OneShotStage.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/Math.h"
# include "Utility/BGM.h"
# include "Utility/Input.h"

# include "Manager/MessageManager.h"
# include "Manager/EndManager.h"

# include "Scene/ISceneMediator.h"
# include "Scene/Scene.h"

# include "Experimental/AnimateState.h"

# include "Stage/ScriptStageDataBuilder.h"

# include "Actor/AnimateActor.h"
# include "Actor/StaticObject.h"
# include "Actor/Field/Field.h"

std::string OneShotStage::m_name;

OneShotStage::OneShotStage()
	: m_world()
	, m_data()
{

}

void OneShotStage::loadContents(Loader& loader)
{
	// loader.loadContent("BaseBook", "Model/本/新本.pmx");
	loader.loadContent("desk", "Model/机/つくえ.mqo");
	loader.loadContent("Message", "Texture/end/message.png");

	ScriptStageDataBuilder().open(
		m_name, m_data);
	for (auto&& resource : m_data.resourceList)
	{
		loader.loadContent(resource.first, resource.second);
	}

	// 最初のステージ
	m_world->apply(m_data, false);
}

void OneShotStage::initialize()
{
	m_world = std::make_shared<World>();

	// 本
	m_world->addActor(ActorTag::Effect, std::make_shared<Field>(
		*m_world, "book", Vector3(0.0f, -5.0f, 0.0f), 3.0f, "Resources/Script/Animation/Book.txt"));
	/*m_world->addActor(ActorTag::Effect, std::make_shared<AnimateActor>(
		*m_world, "BaseBook", Vector3(0.0f, -5.0f, 0.0f), 3.0f));*/
	// 机
	m_world->addActor(ActorTag::Effect, std::make_shared<StaticObject>(
		*m_world, "desk", Vector3(-60.0f, -320.0f, 100.0f), (float)Math::ToRadian(-90.0), 0.8f));

	AnimateActor::AnimationInfo info;
	info.animationNumber = 0;
	info.animationTime = 180.0f;
	m_world->findActor("BaseBook")->sendMessage("Animate", &info);
}

void OneShotStage::update()
{
	BGM::play(m_data.bgmName);

	m_world->update();
}

void OneShotStage::draw(Renderer& render)
{
	m_world->draw(render);
}

void OneShotStage::post()
{
	if (StoryManager::get(BitFlag::GOAL))
	{
		if (EndManager::CanEnd())
		{
			m_manager->changeScene(Scene::End, 60.0f);
			EndManager::SetEnd(false);
			return;
		}
		if (!EndManager::isEnd())
		{
			EndManager::Set("Ending1");
			AnimateState state { "Open", true };
			m_world->findGroup(ActorTag::Field)->sendMessage("Animate", &state);
			AnimateActor::AnimationInfo info;
			info.animationNumber = 0;
			info.animationTime = 180.0f;
			info.isReversed = true;
			m_world->findActor("BaseBook")->sendMessage("Animate", &state);
			return;
		}
	}

	if (MessageManager::CanShow())
	{
		m_manager->pushScene(Scene::Message);
		return;
	}
}

void OneShotStage::cleanUp()
{

}

bool OneShotStage::isSwallow() const
{
	return true;
}

void OneShotStage::load(const std::string& name)
{
	m_name = name;
}
