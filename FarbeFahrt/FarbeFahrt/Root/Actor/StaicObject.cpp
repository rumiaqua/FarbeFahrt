#include "StaicObject.h"
#include "Utility/Math.h"

StaticObject::StaticObject(IWorld & world,const String& modelName, const Vector3 & position) :
BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI))
, m_capsule(position, position, 5.0f)
{
	name = modelName;
}

void StaticObject::onDraw(Renderer & render) const
{
	render.drawNormalModel(name.toNarrow(), getPosition(), getRotation());

	BaseActor::onDraw(render);
}
