#include "LightParticleGenerator.h"
#include "LightParticle.h"
#include "Utility/RandomDevice.hpp"
#include "Utility/Math.h"

#include "Utility/Input.h"

namespace
{
	const float Interval = 0.2f;	//ê∂ê¨ä‘äu
}

LightParticleGenerator::LightParticleGenerator(IWorld & world, const Vector3 & position,float radius)
	: BaseActor(
		world,
		"LightParticleGenerator",
		position,
		Matrix::zero(),
		std::make_unique<Sphere>(Vector3::Zero(), radius))
	, m_timer(0.0f)
	, m_counta(0.0f)
	, m_radius(radius + 5.0f)
	, m_genPos(Vector3::Zero())
{
}

void LightParticleGenerator::onUpdate()
{
	m_timer++;

	if (m_timer / 60 >= Interval)
	{
		m_genPos = Vector3(
			getPosition().x + Math::Cos(m_counta) * m_radius, 
			getPosition().y,
			getPosition().z + Math::Sin(m_counta) * m_radius);
		m_world->addActor(ActorTag::Effect, std::make_shared<LightParticle>(*m_world, m_genPos));

		m_genPos = Vector3(
			getPosition().x + Math::Cos(m_counta + Math::ToRadian(120.0f)) * m_radius,
			getPosition().y, 
			getPosition().z + Math::Sin(m_counta + Math::ToRadian(120.0f)) * m_radius);
		m_world->addActor(ActorTag::Effect, std::make_shared<LightParticle>(*m_world, m_genPos));

		m_genPos = Vector3(
			getPosition().x + Math::Cos(m_counta + Math::ToRadian(240.0f)) * m_radius,
			getPosition().y, 
			getPosition().z + Math::Sin(m_counta + Math::ToRadian(240.0f)) * m_radius);
		m_world->addActor(ActorTag::Effect, std::make_shared<LightParticle>(*m_world, m_genPos));

		m_counta += Interval * 2;
		m_timer = std::fmodf(m_timer, 60 * Interval);
	}
}

void LightParticleGenerator::onMessage(const std::string & message, void * parameter)
{
	if (message == "kill")
	{
		kill();
	}

	BaseActor::onMessage(message, parameter);
}
