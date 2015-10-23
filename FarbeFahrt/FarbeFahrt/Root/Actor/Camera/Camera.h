#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
#include "CameraMode.h"
#include "ChaseFlag.h"
#include "Utility/Input.h"

#include <functional>
#include <unordered_map>

class Camera :
	public BaseActor
{
public:
	explicit Camera(IWorld& world);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	void chaseCamera();
	void fadeInCamera();
	void fadeOutCamera();
	void defaultCamera();
	void fadeInFixCamera();
	void lockCamera();
	void initCamera();
	void cameraSet();
	void toPlayerCamera();
	void toBookCamera();
	void toFixCamera();
	void playerCheck();
	void actorCheck(const std::string actorName);

	std::shared_ptr<BaseActor> actor;
private:
	//ÉJÉÅÉââÒì]
	void rotate(float &x, float &z, const float ang, const float targetX, const float targetY);
	void angleReset(float &ang);
private:
	Vector3 targetPos;
	Vector3 currentPos;
	Vector3 targetRot;
	Vector3 currentRot;
	Vector3 focusRot;
	Vector3 playerPos;
	Vector3 actorPos;

	CameraMode cameraMode;
	ChaseFlag chaseFlag;

	float t = 0.0f;
	float second;
	float ang;

	using Func = std::function<void()>;
	std::unordered_map<CameraMode,Func> funcs;
	std::shared_ptr<BaseActor> player;
};
