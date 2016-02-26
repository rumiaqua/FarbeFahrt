#include "StaticObject.h"
#include "Utility/Math.h"
#include "Collision/ModelCollider.h"
#include "Utility\Debug.h"
#include "Utility\String.h"
StaticObject::StaticObject(IWorld & world,const std::string& modelName, const Vector3 & position) :
BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), //std::make_unique<Sphere>(Vector3::Zero(), 10.0f))
	std::make_unique<ModelCollider>(modelName))
	, m_isVisible(true)
{
	m_name = modelName;
}

StaticObject::StaticObject(IWorld& world, const std::string& modelName, const Vector3& position, float angle, float scale)
	: BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), angle), nullptr)
	, m_scale(scale),m_isVisible(true)
{

}

void StaticObject::onDraw(Renderer & renderer) const
{
	//auto a = m_isVisible;
	Debug::Println(String::Create(m_name, ":", m_isVisible ? "true" : "false"));
	if (m_isVisible)
	{
		
		renderer.setScale(m_name, { m_scale, m_scale, m_scale });
		renderer.drawNormalModel(m_name, getPosition(), getRotation());
	}

	BaseActor::onDraw(renderer);
}

void StaticObject::onMessage(const std::string& message, void* parameter)
{
	if (message == "Visible")
	{
		m_isVisible = true;
	}
	if (message == "Invisible")
	{
		m_isVisible = false;
	}

	BaseActor::onMessage(message, parameter);
}
