#include "World.h"

# include "Actor/SkyDome/Skydome.h"
# include "Actor/Camera/Camera.h"

World::World()
	: m_stage(this)
{
	// スカイドームの初期化
	m_skydome = std::make_shared<Skydome>(*this, "sky");

	m_camera = std::make_shared<Camera>(*this);
}
void World::update()
{
	if (m_skydome)
	{
		m_skydome->update();
	}

	m_stage.update();

	if (m_camera)
	{
		m_camera->update();
	}
}
void World::draw(Renderer& render)const
{
	if (m_skydome)
	{
		m_skydome->draw(render);
	}

	m_stage.draw(render);

	if (m_camera)
	{
		m_camera->draw(render);
	}
}
void World::addActor(ActorTag tag, const Actor& actor)
{
	// m_actors.addActor(tag, actor);
	m_stage.addActor(tag, actor);
}
void World::addCamera(const Actor& camera)
{
	m_camera = camera;
}
void World::addSkydome(const Actor& sky)
{
	m_skydome = sky;
}
void World::addField(const Actor& field)
{
	// m_field = field;
}
Actor World::findActor(const std::string& name) const
{
	return m_stage.findActor(name);
}
Actor World::findCamera() const
{
	return m_camera;
}
Actor World::findField() const
{
	return m_stage.findField();
}

StageData World::getData() const
{
	StageData data;

	return data;
}

void World::initFlag()
{
	m_storymanager.initialize();
}

int World::getFlag()
{
	return m_storymanager.getFlag();
}

void World::setFlag(int flag)
{
	m_storymanager.setFlag(flag);
}

void World::apply(const StageData& data)
{
	m_stage.apply(data);
}