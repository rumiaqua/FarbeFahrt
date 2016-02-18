# include "StageData.h"

StageData::FieldObj::FieldObj(const std::string& name, const Vector3& position, float scale, const std::string& transition, float animationTime)
	: name(name)
	, position(position)
	, scale(scale)
	, transition(transition)
	, animationTime(animationTime)
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
