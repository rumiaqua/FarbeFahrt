# pragma once

# include "Vector3.h"
# include "String.h"

# include <vector>
# include <unordered_map>

class World;
class String;

class StageFactory
{
public:

	void Load(const String& filename);

	void Apply(World& world) const;

	const std::unordered_map<String, String>& Resources() const;

private:

	std::vector<std::string> Split(const std::string& str, char delim);

	float ToFloat(const std::string& str);

	Vector3 ToVector3(const std::string& s1, const std::string& s2, const std::string& s3);

private:

	struct Data
	{
		std::unordered_map<String, String> resourceList;
		Vector3 playerPosition;
		struct Object
		{
			String name;
			String resource;
			Vector3 position;
			Object(const String& name, const String& resource, const Vector3& position);
		};
		std::vector<Object> objectList;
	} m_data;
};
