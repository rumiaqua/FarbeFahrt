#pragma once
#include "BaseActor.h"
class Enemy :
	public BaseActor
{
public:
	Enemy(IWorld& world);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
private:
};