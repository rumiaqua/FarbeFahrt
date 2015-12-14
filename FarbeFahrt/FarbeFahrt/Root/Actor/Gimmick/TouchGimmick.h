#pragma once
#include "Actor/BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class TouchGimmick :
	public BaseActor
{
public:
	TouchGimmick(IWorld& world, const std::string& modelName, const Vector3& position, float radius);
private:
	virtual void onUpdate()override;
	virtual void onMessage(const std::string& message, void* parameter)override;
private:
	bool m_flag;
};
