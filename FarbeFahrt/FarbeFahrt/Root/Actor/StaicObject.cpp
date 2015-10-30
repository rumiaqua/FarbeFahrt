#include "StaicObject.h"
#include "Utility/Math.h"

StaticObject::StaticObject(IWorld & world,const std::string modelName, const Vector3 & position) :
	BaseActor(world, modelName, position, Matrix::rotation(Vector3::up(), Math::Pi)
{

}
