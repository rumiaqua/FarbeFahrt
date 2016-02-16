#pragma once

#include "Actor/BaseActor.h"
#include "Utility/Math.h"

class LightParticleGenerator : public BaseActor
{
public:
	LightParticleGenerator(IWorld& world, const Vector3& position,float radius);

private:
	virtual void onUpdate()override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:
	float m_timer;
	float m_counta;
	float m_radius;
	Vector3 m_genPos;
	bool m_isActive;
};
