# pragma once

# include "Utility/String.h"
# include "Utility/Vector3.h"

# include <unordered_map>

class IShape;

struct StageData
{
	struct Object
	{
		String name;
		String resource;
		Vector3 position;
		String shape;
		String parameter;
		Object(const String& name, const String& resource, const Vector3& position, const String& shape, const String& parameter);
	};

	using ResourceList = std::unordered_map<String, String>;
	using ObjectList = std::vector<Object>;

	ResourceList resourceList;
	Vector3 playerPosition;
	String fieldName;
	float fieldScale;
	String skyName;
	ObjectList objectList;
};
