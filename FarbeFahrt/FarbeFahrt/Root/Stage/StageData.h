# pragma once

# include "Utility/String.h"
# include "Utility/Vector3.h"

# include <unordered_map>

class IShape;

struct StageData
{
	struct FieldObj
	{
		std::string name;
		Vector3 position;
		float scale;
		FieldObj(const std::string& name, const Vector3& position, float scale);
	};

	struct Object
	{
		std::string name;
		std::string resource;
		Vector3 position;
		std::string shape;
		std::string parameter;
		Object(const std::string& name, const std::string& resource, const Vector3& position, const std::string& shape, const std::string& parameter);
	};

	using ResourceList = std::unordered_map<std::string, std::string>;
	using FieldList = std::vector<FieldObj>;
	using ObjectList = std::vector<Object>;
	using NextStage = std::pair<std::string, std::string>;
	using Messages = std::vector<std::string>;

	std::string filename;
	ResourceList resourceList;
	Vector3 playerPosition;
	FieldList fieldList;
	ObjectList objectList;
	NextStage nextStage;
	int endNum;
	Messages message;
	int gimmickPoint;
};
