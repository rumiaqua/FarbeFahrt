# pragma once

# include "Actor/BaseActor.h"

class Instant : public BaseActor
{
public:

	Instant(IWorld& world, const std::string& name, const Vector3& position, const std::vector<std::string>& parameters);

private:

	virtual void onUpdate() override;
	virtual void onDraw(Renderer& renderer) const override;

public:

	virtual void onMessage(const std::string& message, void* parameter);

private:

	bool m_isGravity;
	bool m_isActive;
	std::weak_ptr<BaseActor> m_particleSystem;
};
