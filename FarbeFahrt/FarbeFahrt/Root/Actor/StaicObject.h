#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class StaticObject :
	public BaseActor
{
public:
	StaticObject(IWorld& world,const std::string modelName,const Vector3& position);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;

private:
	Capsule capsule;
};
