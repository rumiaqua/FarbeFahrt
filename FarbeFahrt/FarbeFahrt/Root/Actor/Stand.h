#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"

class Stand :
	public BaseActor
{
public:
	Stand(IWorld& world, const Vector3& position);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	virtual void onMessage(const String& message, const void* parameter)override;

private:
	Capsule m_capsule;
};
