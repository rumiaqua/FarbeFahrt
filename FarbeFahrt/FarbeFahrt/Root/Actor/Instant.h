# pragma once

# include "Actor/BaseActor.h"

class Instant : public BaseActor
{
public:

	Instant(IWorld& world, const std::string& name, const Vector3& position);

private:

	virtual void onUpdate() override;
	virtual void onDraw(Renderer& renderer) const override;

public:

	virtual void onMessage(const std::string& message, void* parameter);

private:

	bool m_isGravity;
};
