#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
class Field :
	public BaseActor
{
public:
	explicit Field(IWorld& world);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	virtual void onCollide(BaseActor& actor) override;
public:

private:
};
