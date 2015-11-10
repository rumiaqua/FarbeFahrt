#include "SkinObject.h"
#include "Utility/Math.h"

#include "Utility/Input.h"

namespace 
{
	float flame = 0.0f;
}

SkinObject::SkinObject(IWorld & world, const String& modelName, const Vector3 & position, int anmNo, float flameSpeed,float maxFlame) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), nullptr)
{
	m_name = modelName;
	m_flameSpeed = flameSpeed;
	m_maxFlame = maxFlame;
	m_anmNo = anmNo;
}

void SkinObject::flameReset()
{
	flame = 0;
}

void SkinObject::onUpdate()
{
	if(flame <= m_maxFlame * m_flameSpeed)
	{
		flame += m_flameSpeed;
	}
	BaseActor::onUpdate();
}

void SkinObject::onDraw(Renderer & render) const
{
	render.drawSkinModel(m_name.toNarrow(), getPosition(), getRotation(), m_anmNo, flame);

	BaseActor::onDraw(render);
}

void SkinObject::onMessage(const String & message, void* parameter)
{
	/*if (message == "Rotation")
		Matrix::Rotate(getRotation(), Vector3::Up(), *(const float*)parameter);*/
	BaseActor::onMessage(message, parameter);
}