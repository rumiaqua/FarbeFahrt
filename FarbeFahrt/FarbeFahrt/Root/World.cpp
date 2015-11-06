#include "World.h"

World::World()
{
}
void World::update()
{
	m_sky->update();
	m_field->update();
	m_actors.update();
	m_camera->update();
}
void World::draw(Renderer& render)const
{
	m_sky->draw(render);
	m_field->draw(render);
	m_actors.draw(render);
	m_camera->draw(render);
}
void World::addActor(ActorTag tag, const Actor& actor)
{
	m_actors.addActor(tag, actor);
}
void World::addCamera(const Actor& camera)
{
	m_camera = camera;
}
void World::addSkydome(const Actor& sky)
{
	m_sky = sky;
}
void World::addField(const Actor& field)
{
	m_field = field;
}
Actor World::findActor(const std::string& name) const
{
	return m_actors.findActor(name);
}
Actor World::findCamera() const
{
	return m_camera;
}
Actor World::findField() const
{
	return m_field;
}

StageData World::getData() const
{
	StageData data;

	data.resourceList["Player"] = "Model/MMD–‚“±Žo’íVer1.1/ƒKƒuƒŠƒGƒ‰.pmx";
	data.resourceList["sky"] = "Model/skydome/’‹‚ÌŒŽ.x";
	data.resourceList["field"] = "Model/terrain/terrain.mqo";

	data.playerPosition = Vector3(0, 0, 0);

	data.objectList.emplace_back("Enemy", "Player", Vector3(0, 0, 100));
	data.objectList.emplace_back("Item", "Player", Vector3(100, 0, 0));

	return data;
}
