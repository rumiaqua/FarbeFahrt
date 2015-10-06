#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"

#include "Utility/Input.h"

class Camera :
	public BaseActor
{
public:
	Camera(IWorld& world);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
private:
	//ÉJÉÅÉââÒì]
	void rotate(float &x, float &z, const float ang, const float targetX, const float targetY);
	void angleReset(float &ang);
private:
	POINT mousePos;
	VECTOR targetPos;
	VECTOR currentPos;
	VECTOR targetRot;
	VECTOR currentRot;
	VECTOR focusRot;
	VECTOR focus;
	VECTOR dif;

	bool fadeFlag = false;

	float t = 0.0f;
	float second;
	float ang;
};
