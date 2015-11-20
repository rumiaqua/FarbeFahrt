# pragma once

# include "BaseActor.h"

class PlayerSpawner : public BaseActor
{
public:

	PlayerSpawner(IWorld& world, const String& name, const Vector3& position);

public:

	virtual void onUpdate() override;

	virtual void onMessage(const String& message, void * parameter) override;
};
