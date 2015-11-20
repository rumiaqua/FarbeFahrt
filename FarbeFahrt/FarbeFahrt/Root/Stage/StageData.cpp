# include "StageData.h"

StageData::FieldObj::FieldObj(const String& name, const Vector3& position, float scale)
	: name(name)
	, position(position)
	, scale(scale)
{

}

StageData::Object::Object(const String& name, const String& resource, const Vector3& position, const String& shape, const String& parameter)
	: name(name)
	, resource(resource)
	, position(position)
	, shape(shape)
	, parameter(parameter)
{

}
