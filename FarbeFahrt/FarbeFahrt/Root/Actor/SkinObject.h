#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class SkinObject :
	public BaseActor
{
public:
	SkinObject(IWorld& world, const String& modelName, const Vector3& position, int anmNo,float frameSpeed,float maxframe, float scale, float angle, bool isLoop);
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
	float m_scale;
	bool m_isLoop;
};
