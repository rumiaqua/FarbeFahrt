#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
#include "Utility/Input.h"
#include "CameraState.h"
#include "CameraMatrix.h"
#include "World.h"

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
	void cameraInput();
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
	float m_t = 0.0f;

	CameraState m_cameraState;
	CameraMatrix m_cameraMatrix;
	std::shared_ptr<BaseActor> m_actor;
};
