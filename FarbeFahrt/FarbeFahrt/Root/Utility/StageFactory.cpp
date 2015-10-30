# include "StageFactory.h"

# include "World.h"

# include "Actor/Player.h"
# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"
# include "Actor/Field/Field.h"
# include "Actor/Enemy.h"

# include "IStageBuilder.h"
# include "ScriptStageBuilder.h"

void StageFactory::Load(const String& filename)
{
	ScriptStageBuilder builder;

	m_data = builder.open(filename);
}

void StageFactory::Apply(World& world) const
{
	world.addCamera(std::make_shared<Camera>(world));
	world.addField(std::make_shared<Field>(world));
	world.addSkydome(std::make_shared<Skydome>(world));

	world.addActor(ActorTag::Player, std::make_shared<Player>(
		world, m_data.playerPosition));
	
	for (auto&& object : m_data.objectList)
	{
		ActorTag tag;
		if (object.name == "Enemy")
		{
			tag = ActorTag::Enemy;
		}
		if (object.name == "Item")
		{
			tag = ActorTag::Item;
		}

		world.addActor(tag, std::make_shared<Enemy>(
			world, object.position, object.resource));
	}
}

const std::unordered_map<String, String>& StageFactory::Resources() const
{
	return m_data.resourceList;
}
