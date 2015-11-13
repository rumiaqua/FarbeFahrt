#pragma once
#include "Actor/BaseActor.h"
#include "Collision/Line.h"

class Ray :
	public BaseActor
{
public:
	Ray(IWorld& world, const Vector3& begin,const Vector3& end);

private:
	virtual void onUpdate() override;
	virtual void onMessage(const String& message, void* parameter) override;
};
