#pragma once
#include "Actor/BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class Goal :
	public BaseActor
{
public:
	Goal(IWorld& world, const String& modelName, const Vector3& position);
private:
	virtual void onDraw(Renderer& render)const override;
	virtual void onMessage(const String& message, void* parameter) override;

private:
	Capsule m_capsule;
};