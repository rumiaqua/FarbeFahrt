# include "StageFactory.h"

# include "World.h"

# include "Actor/Player.h"
# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"
# include "Actor/Field/Field.h"
# include "Actor/Gimmick/Gimmick.h"

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
	world.addField(std::make_shared<Field>(world, m_data.fieldName, m_data.fieldScale));
	world.addSkydome(std::make_shared<Skydome>(world, m_data.skyName));

	world.addActor(ActorTag::Player, std::make_shared<Player>(
		world, m_data.playerPosition));
	
	for (auto&& object : m_data.objectList)
	{
		if (object.name == "Gimmick")
		{
			world.addActor(ActorTag::Gimmick, std::make_shared<Gimmick>(
				world, object.resource, object.position, 1, 1.0f, 300.0f));
		}
	}
}

const std::unordered_map<String, String>& StageFactory::Resources() const
{
	return m_data.resourceList;
}

const StageData& StageFactory::Data() const
{
	return m_data;
}
