# include "StageData.h"

StageData::Object::Object(const String& name, const String& resource, const Vector3& position, IShape* shape)
	: name(name)
	, resource(resource)
	, position(position)
	, shape(shape)
{

}
