#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
class Camera :
	public BaseActor
{
public:
	Camera(IWorld& world);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
private:
	//ƒJƒƒ‰‰ñ“]
	void rotate(float &x, float &z, const float ang, const float targetX, const float targetY);
	void angleReset(float &ang);
private:
	POINT mousePos;
	VECTOR targetPos;
	float ang;
};
