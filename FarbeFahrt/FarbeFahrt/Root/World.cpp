#include "World.h"

World::World(ISceneMediator* manager)
	: m_stage(this,manager)
{
	// カメラの初期化
	m_camera = std::make_shared<Camera>(*this);
}
void World::update()
{
	m_stage.update();

	if (m_camera)
	{
		m_camera->update();
	}
}
void World::draw(Renderer& renderer)const
{
	m_stage.draw(renderer);

	if (m_camera)
	{
		m_camera->draw(renderer);
	}
}
void World::addActor(ActorTag tag, const Actor& actor)
{
	m_stage.addActor(tag, actor);
}
void World::addCamera(const Actor& camera)
{
	m_camera = camera;
}
Actor World::findActor(const std::string& name) const
{
	return m_stage.findActor(name);
}
std::vector<Actor> World::findActors(const std::string& name) const
{
	return m_stage.findActors(name);
}
Actor World::findCamera() const
{
	return m_camera;
}

Actor World::findGroup(const ActorTag& tag) const
{
	return m_stage.findGroup(tag);
}

StageData World::getData() const
{
	return StageData();
}

void World::apply(const StageData& data, bool isClear)
{
	m_stage.apply(data, isClear);
}

//こっちの旧actorSetは後に削除
void World::actorSet(const std::string& actorName)
{
	m_camera->sendMessage("actorSet",(void*)&actorName);
}

void World::actorSet(const Vector3& position)
{
	m_camera->sendMessage("actorSet", (void*)&position);
}

void World::clearActor()
{
	m_stage.clearActor();
}
