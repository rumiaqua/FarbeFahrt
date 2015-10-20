#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
#include "CameraMode.h"
#include "Utility/Input.h"

#include <functional>
#include <unordered_map>

class Camera :
	public BaseActor
{
public:
	Camera(IWorld& world);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	void chaseCamera();
	void fadeInCamera();
	void fadeOutCamera();
	void defaultCamera();
	void initCamera();
	void cameraSet();
	void toPlayerCamera();
	void toBookCamera();
	void cameraControl();
	void playerCheck();
private:
	//ÉJÉÅÉââÒì]
	void rotate(float &x, float &z, const float ang, const float targetX, const float targetY);
	void angleReset(float &ang);
private:
	VECTOR targetPos;
	VECTOR currentPos;
	VECTOR targetRot;
	VECTOR currentRot;
	VECTOR focusRot;
	VECTOR dif;
	VECTOR playerPos;

	bool chaseFlag;

	CameraMode cameraMode;

	float t = 0.0f;
	float second;
	float ang;

	using Func = std::function<void()>;
	std::unordered_map<CameraMode,Func> funcs;
	std::shared_ptr<BaseActor> player;
};
