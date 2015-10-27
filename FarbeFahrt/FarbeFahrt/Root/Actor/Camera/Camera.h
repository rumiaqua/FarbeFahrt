#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
#include "Utility/Input.h"
#include "CameraState.h"
#include "CameraMatrix.h"

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
	
private:	
	float t = 0.0f;

	CameraState cameraState;
	CameraMatrix cameraMatrix;	
	std::shared_ptr<BaseActor> actor;
};
