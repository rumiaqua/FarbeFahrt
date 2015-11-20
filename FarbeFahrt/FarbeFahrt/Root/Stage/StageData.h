# pragma once

# include "Utility/String.h"
# include "Utility/Vector3.h"

# include <unordered_map>

class IShape;

struct StageData
{
	struct FieldObj
	{
		String name;
		Vector3 position;
		float scale;
		FieldObj(const String& name, const Vector3& position, float scale);
	};

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
	using FieldList = std::vector<FieldObj>;
	using ObjectList = std::vector<Object>;
	using NextStage = std::pair<String, String>;

	ResourceList resourceList;
	Vector3 playerPosition;
	FieldList fieldList;
	ObjectList objectList;
	NextStage nextStage;
};
