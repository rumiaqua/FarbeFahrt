#include "World.h"

World::World()
{
}
void World::update()
{
	sky->update();
	field->update();
	actors.update();
	camera->update();
}
void World::draw(Renderer& render)const
{
	sky->draw(render);
	field->draw(render);
	actors.draw(render);
	camera->draw(render);
}
void World::addActor(ActorTag tag, const Actor& actor)
{
	actors.addActor(tag, actor);
}
void World::addCamera(const Actor& camera)
{
	this->camera = camera;
}
void World::addSkydome(const Actor& sky)
{
	this->sky = sky;
}
void World::addField(const Actor& field)
{
	this->field = field;
}
Actor World::findActor(const std::string& name)
{
	return actors.findActor(name);
}
Actor World::findCamera()
{
	return camera;
}
Actor World::findField()
{
	return field;
}