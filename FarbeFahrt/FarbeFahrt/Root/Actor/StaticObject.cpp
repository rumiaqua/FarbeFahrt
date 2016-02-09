#include "StaticObject.h"
#include "Utility/Math.h"
#include "Collision/ModelCollider.h"

StaticObject::StaticObject(IWorld & world,const std::string& modelName, const Vector3 & position) :
BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), //std::make_unique<Sphere>(Vector3::Zero(), 10.0f))
	std::make_unique<ModelCollider>(modelName))
{
	m_name = modelName;
}

StaticObject::StaticObject(IWorld& world, const std::string& modelName, const Vector3& position, float angle, float scale)
	: BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), angle), nullptr)
	, m_scale(scale)
{

}

void StaticObject::onDraw(Renderer & renderer) const
{
	renderer.setScale(m_name, { m_scale, m_scale, m_scale });
	renderer.drawNormalModel(m_name, getPosition(), getRotation());

	BaseActor::onDraw(renderer);
}
