# pragma once

# include "Actor/BaseActor.h"

class Herb : public BaseActor
{
public:

	Herb(IWorld& world, const Vector3& position);

private:

	virtual void onUpdate();

public:

	virtual void onMessage(const std::string& message, void* parameter);

private:

	float m_gravity;
};
