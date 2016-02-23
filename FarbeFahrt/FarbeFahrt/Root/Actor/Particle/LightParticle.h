#pragma once

#include "Actor/BaseActor.h"
#include "Utility/Math.h"

class LightParticle : public BaseActor
{
public:
	LightParticle(IWorld& world, const Vector3& position);

private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& renderer) const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:
	int m_alpha;
	float m_angle;
	float m_timer;
	int m_rand;
};