# include "StageData.h"

StageData::FieldObj::FieldObj(const std::string& name, const Vector3& position, float scale)
	: name(name)
	, position(position)
	, scale(scale)
{

}

StageData::Object::Object(const std::string& name, const std::string& resource, const Vector3& position, const std::string& shape, const std::string& parameter)
	: name(name)
	, resource(resource)
	, position(position)
	, shape(shape)
	, parameter(parameter)
{

}
