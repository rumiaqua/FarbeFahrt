#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"

#include "Utility/Input.h"

# include "Utility/Point2.h"

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
	Point2 mousePos;
	Vector3 targetPos;
	Vector3 currentPos;
	Vector3 targetRot;
	Vector3 currentRot;
	Vector3 focusRot;
	Vector3 focus;
	Vector3 dif;

	bool fadeFlag = false;

	float t = 0.0f;
	float second;
	float ang;
};
