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
	m_actors[ActorTag::Object] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Item] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Effect] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Gimmick] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Collider] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Goal] = std::make_shared<BaseActor>();
	m_actors[ActorTag::Field] = std::make_shared<BaseActor>();
	m_root.eachChildren([] (BaseActor& actor) { actor.kill(); });
	m_root.removeChildren();
	m_root.addChild(m_actors[ActorTag::Player]);
	m_root.addChild(m_actors[ActorTag::Enemy]);
	m_root.addChild(m_actors[ActorTag::Object]);
	m_root.addChild(m_actors[ActorTag::Item]);
	m_root.addChild(m_actors[ActorTag::Effect]);
	m_root.addChild(m_actors[ActorTag::Gimmick]);
	m_root.addChild(m_actors[ActorTag::Collider]);
	m_root.addChild(m_actors[ActorTag::Goal]);
	m_root.addChild(m_actors[ActorTag::Field]);
}
void ActorManager::update()
{
	// XVˆ—
	m_root.update();

	// Õ“Ëˆ—
	BaseActor& enemys = *m_actors[ActorTag::Enemy];
	BaseActor& players = *m_actors[ActorTag::Player];
	BaseActor& colliders = *m_actors[ActorTag::Collider];
	BaseActor& gimmicks = *m_actors[ActorTag::Gimmick];
	BaseActor& goal = *m_actors[ActorTag::Goal];
	BaseActor& objects = *m_actors[ActorTag::Object];

	enemys.eachChildren(
		[&] (BaseActor& actor) { players.collide(&actor); });
	gimmicks.eachChildren(
		[&] (BaseActor& actor) { colliders.collide(&actor); });

	if (auto&& player = findActor("Player"))
	{
		goal.collide(&*player);
		objects.collide(&*player);
	}

	// íœˆ—
	m_root.removeChildren();
}
void ActorManager::draw(Renderer& renderer)const
{
	m_root.draw(renderer);
}
void ActorManager::addActor(ActorTag tag, const Actor& actor)
{
	m_actors[tag]->addChild(actor);
}

Actor ActorManager::findActor(const std::string& name) const
{
	return m_root.find(name);
}

std::vector<Actor> ActorManager::findActors(const std::string& name) const
{
	return m_root.finds(name);
}

Actor ActorManager::findGroup(const ActorTag& tag) const
{
	return m_actors.at(tag);
}

void ActorManager::collidePlayer(ActorTag tag)
{
	// field->collide(m_actors.at(ActorTag::Player).get());
	m_actors.at(tag)->eachChildren([=] (BaseActor& actor)
	{
		m_actors.at(ActorTag::Player)->collide(&actor);
	});
	// m_actors.at(ActorTag::Player)->collide(field);
}
