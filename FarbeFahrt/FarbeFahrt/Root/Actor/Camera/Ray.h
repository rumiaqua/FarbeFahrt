#pragma once
#include "Actor/BaseActor.h"
#include "Collision/Line.h"

class Ray :
	public BaseActor
{
public:
	Ray(IWorld& world, const Vector3& begin,const Vector3& end);

private:
	void onUpdate() override;
	void onCollide(BaseActor& actor) override;
};