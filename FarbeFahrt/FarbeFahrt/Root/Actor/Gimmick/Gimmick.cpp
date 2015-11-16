#include "Gimmick.h"
#include "Utility/Math.h"
#include "Utility/Input.h"

#include "Utility/Debug.h"

namespace
{
	float flame = 0.0f;
}

Gimmick::Gimmick(IWorld & world, const String& modelName, const Vector3 & position, int anmNo, float flameSpeed, float maxFlame) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Sphere>(Vector3::Zero(), 5.0f))
{
	m_name = modelName;
	m_flameSpeed = flameSpeed;
	m_maxFlame = maxFlame;
	m_anmNo = anmNo;
}

void Gimmick::flameReset()
{
	flame = 0;
}

void Gimmick::onUpdate()
{
	if (flame <= m_maxFlame * m_flameSpeed)
	{
		flame += m_flameSpeed;
	}
	BaseActor::onUpdate();
}

void Gimmick::onDraw(Renderer & render) const
{
	render.drawSkinModel(m_name.toNarrow(), getPosition(), getRotation(), m_anmNo, flame);

	BaseActor::onDraw(render);
}

void Gimmick::onMessage(const String & message, void* parameter)
{
	if (message == "HitGimmick")
	{
		m_world->setFlag(BitFlag::GIMMICK);
		kill();
	}
	BaseActor::onMessage(message, parameter);
}