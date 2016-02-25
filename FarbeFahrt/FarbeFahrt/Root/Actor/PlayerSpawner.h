# pragma once

# include "BaseActor.h"

class PlayerSpawner : public BaseActor
{
public:

	PlayerSpawner(IWorld& world, const Vector3& position, const std::vector<Vector4>& noEntries);

public:

	virtual void onMessage(const std::string& message, void * parameter) override;

private:

	bool m_isActive;
	std::vector<Vector4> m_noEntries;
};
