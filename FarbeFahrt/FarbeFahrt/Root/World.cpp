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

	return data;
}
