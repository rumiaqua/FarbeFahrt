# pragma once

# include "BaseActor.h"

class Boat : public BaseActor
{
public:

	Boat(IWorld& world, const std::string& name, const Vector3& position);

private:

	virtual void onUpdate() override;
	virtual void onDraw(Renderer& renderer) const override;

public:

	virtual void onMessage(const std::string& message, void* parameter);

private:

	bool m_isActive;
	std::weak_ptr<BaseActor> m_player;
	Vector3 m_relative;
	float m_delay;
};
