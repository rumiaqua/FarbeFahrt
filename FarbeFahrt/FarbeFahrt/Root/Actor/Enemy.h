#pragma once
#include "BaseActor.h"
class Enemy :
	public BaseActor
{
public:
	explicit Enemy(IWorld& world, const Vector3& position, const String& name);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
private:
};
