#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class SkinObject :
	public BaseActor
{
public:
	SkinObject(IWorld& world, const String& modelName, const Vector3& position, int anmNo,float flameSpeed,float maxFlame);
	void flameReset();
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	virtual void onMessage(const String& message, void* parameter)override;

private:
	float m_flameSpeed;
	float m_maxFlame;
	int m_anmNo;
};
