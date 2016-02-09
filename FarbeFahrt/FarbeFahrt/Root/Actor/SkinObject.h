#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"
#include "Actor/Gimmick/GimmickManager.h"

#include "Camera/Camera.h"

class SkinObject :
	public BaseActor
{
public:
	SkinObject(IWorld& world, const std::string& modelName, const Vector3& position, int anmNo,float frameSpeed,float maxframe, float scale, float angle, bool isLoop,float radius);
	void frameReset();
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& renderer)const override;
	virtual void onMessage(const std::string& message, void* parameter)override;
private:
	void animation();
private:
	float m_frameSpeed;
	float m_maxframe;
	int m_anmNo;
	bool isAnimate;
	float m_scale;
	bool m_isLoop;
	int m_point;

	bool drawFlag;
};
