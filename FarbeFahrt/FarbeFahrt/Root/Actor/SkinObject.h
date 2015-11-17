#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class SkinObject :
	public BaseActor
{
public:
	SkinObject(IWorld& world, const String& modelName, const Vector3& position, int anmNo,float frameSpeed,float maxframe);
	void frameReset();
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	virtual void onMessage(const String& message, void* parameter)override;
private:
	void animation();
private:
	float m_frameSpeed;
	float m_maxframe;
	int m_anmNo;
	bool isAnimate;
};
