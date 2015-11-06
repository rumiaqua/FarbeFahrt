#include "ActorManager.h"

ActorManager::ActorManager()
	: m_root()
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
	m_root.removeChildren();
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

	BaseActor& enemys = *m_actors[ActorTag::Enemy];
	BaseActor& players = *m_actors[ActorTag::Player];

	enemys.eachChildren(
		[&] (BaseActor& actor) { players.collide(actor); });
}
void ActorManager::draw(Renderer& render)const
{
	m_root.draw(render);
}
void ActorManager::addActor(ActorTag tag, const Actor& actor)
{
	m_actors[tag]->addChild(actor);
}

Actor ActorManager::findActor(const String& name) const
{
	return m_root.find(name);
}
