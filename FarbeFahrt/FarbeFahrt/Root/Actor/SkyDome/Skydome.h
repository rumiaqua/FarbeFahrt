#pragma once
#include "Root/Actor/BaseActor.h"
#include "Utility/Def.h"
class Skydome :
	public BaseActor
{
public:
	Skydome(IWorld& world);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
private:
};
