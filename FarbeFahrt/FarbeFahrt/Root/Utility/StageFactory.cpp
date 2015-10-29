# include "StageFactory.h"

# include "World.h"

# include "Actor/Player.h"
# include "Actor/Camera/Camera.h"
# include "Actor/SkyDome/Skydome.h"
# include "Actor/Field/Field.h"
# include "Actor/Enemy.h"

# include <fstream>
# include <sstream>

void StageFactory::Load(const String& filename)
{
	std::ifstream stream(filename.toNarrow());

	std::string buffer;
	while (std::getline(stream, buffer))
	{
		if (buffer[0] == '#')
		{
			continue;
		}

		std::vector<std::string> split = Split(buffer, ',');
		
		if (split.empty())
		{
			continue;
		}

		if (split[0] == "r")
		{
			m_data.resourceList.insert(std::make_pair(split[1], split[2]));
		}

		if (split[0] == "p")
		{
			m_data.playerPosition = ToVector3(split[1], split[2], split[3]);
		}

		if (split[0] == "o")
		{
			m_data.objectList.emplace_back(split[1], split[2], ToVector3(split[3], split[4], split[5]));
		}
	}
}

void StageFactory::Apply(World& world) const
{
	world.addCamera(std::make_shared<Camera>(world));
	world.addField(std::make_shared<Field>(world));
	world.addSkydome(std::make_shared<Skydome>(world));

	world.addActor(ActorTag::Player, std::make_shared<Player>(world, m_data.playerPosition));
	
	for (auto&& object : m_data.objectList)
	{
		if (object.name == "Enemy")
		{
			world.addActor(ActorTag::Enemy, std::make_shared<Enemy>(world, object.position, object.resource));
		}
	}
}

const std::unordered_map<String, String>& StageFactory::Resources() const
{
	return m_data.resourceList;
}

std::vector<std::string> StageFactory::Split(const std::string& str, char delim)
{
	std::vector<std::string> res;
	size_t current = 0, found;

	while ((found = str.find_first_of(delim, current)) != std::string::npos)
	{
		res.push_back(std::string(str, current, found - current));
		current = found + 1;
	}
	res.push_back(std::string(str, current, str.size() - current));
	return res;
}

float StageFactory::ToFloat(const std::string& str)
{
	std::istringstream ifs { str };
	float res;
	ifs >> res;
	return res;
}

Vector3 StageFactory::ToVector3(const std::string& s1, const std::string& s2, const std::string& s3)
{
	return Vector3(ToFloat(s1), ToFloat(s2), ToFloat(s3));
}

StageFactory::Data::Object::Object(const String& name, const String& resource, const Vector3& position)
	: name(name)
	, resource(resource)
	, position(position)
{

}
