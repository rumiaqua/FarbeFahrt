#include "ActorManager.h"

# include "Actor/Field/Field.h"

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
	m_actors[ActorTag::Gimmick] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Collider] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Goal] = std::make_shared<BaseActor>();
	m_root.removeChildren();
	m_root.addChild(m_actors[ActorTag::Player]);
	m_root.addChild(m_actors[ActorTag::Enemy]);
	m_root.addChild(m_actors[ActorTag::NPC]);
	m_root.addChild(m_actors[ActorTag::Item]);
	m_root.addChild(m_actors[ActorTag::Effect]);
	m_root.addChild(m_actors[ActorTag::Gimmick]);
	m_root.addChild(m_actors[ActorTag::Collider]);
	m_root.addChild(m_actors[ActorTag::Goal]);
}
void ActorManager::update()
{
	m_root.update();
	m_root.removeChildren();

	BaseActor& enemys = *m_actors[ActorTag::Enemy];
	BaseActor& players = *m_actors[ActorTag::Player];
	BaseActor& colliders = *m_actors[ActorTag::Collider];
	BaseActor& gimmicks = *m_actors[ActorTag::Gimmick];
	BaseActor& goal = *m_actors[ActorTag::Goal];

	enemys.eachChildren(
		[&] (BaseActor& actor) { players.collide(&actor); });
	gimmicks.eachChildren(
		[&](BaseActor& actor) { colliders.collide(&actor); });

	auto& player = findActor("Player");
	if (!player)
	{
		return;
	}

	goal.collide(&*player);
}
void ActorManager::draw(Renderer& render)const
{
	m_root.draw(render);
}
void ActorManager::addActor(ActorTag tag, const Actor& actor)
{
	m_actors[tag]->addChild(actor);
}

Actor ActorManager::findActor(const std::string& name) const
{
	return m_root.find(name);
}

void ActorManager::collideField(BaseActor* field)
{
	// field->collide(m_actors.at(ActorTag::Player).get());
	m_actors.at(ActorTag::Player)->collide(field);
}
