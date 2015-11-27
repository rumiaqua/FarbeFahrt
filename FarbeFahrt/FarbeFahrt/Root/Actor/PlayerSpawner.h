# pragma once

# include "BaseActor.h"

class PlayerSpawner : public BaseActor
{
public:

	PlayerSpawner(IWorld& world, const Vector3& position);

public:

	virtual void onUpdate() override;

	virtual void onMessage(const std::string& message, void * parameter) override;

private:

	bool m_isActive;
};
