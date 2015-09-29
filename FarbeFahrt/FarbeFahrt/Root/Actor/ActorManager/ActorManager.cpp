#include "ActorManager.h"

ActorManager::ActorManager()
{
	initialize();
}
void ActorManager::initialize()
{
	m_actors[ActorTag::Player] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Enemy] = std::make_shared<BaseActor>();
	m_actors[ActorTag::NPC] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Item] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Effect] = std::make_shared<BaseActor>();
	m_root.clearChildren();
	m_root.addChild(m_actors[ActorTag::Player]);
	m_root.addChild(m_actors[ActorTag::Enemy]);
	m_root.addChild(m_actors[ActorTag::NPC]);
	m_root.addChild(m_actors[ActorTag::Item]);
	m_root.addChild(m_actors[ActorTag::Effect]);
}
void ActorManager::update()
{
	m_root.update();
	m_root.removeChildren();
}
void ActorManager::draw(Renderer& render)const
{
	m_root.draw(render);
}
void ActorManager::addActor(ActorTag tag, const Actor& actor)
{
	m_actors[tag]->addChild(actor);
}
Actor ActorManager::findActor(const std::string& name)
{
	return m_root.findChildren(name);
}