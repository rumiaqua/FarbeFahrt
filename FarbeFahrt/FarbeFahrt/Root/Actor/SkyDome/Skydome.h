#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
class Skydome :
	public BaseActor
{
public:
	explicit Skydome(IWorld& world, const std::string& name);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
private:
};
