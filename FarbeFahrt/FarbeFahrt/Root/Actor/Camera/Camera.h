#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
#include "Utility/Input.h"
#include "CameraState.h"
#include "CameraMatrix.h"
#include "World.h"
#include "Utility/Optional.h"

#include <functional>
#include <unordered_map>

struct GimmickData
{
	bool switching = false;
	float timer = 0.0f;
};

class Camera :
	public BaseActor
{
public:
	explicit Camera(IWorld& world);
	void actorSet(const std::string& actorName);
	void actorSet(const Vector3& position);

private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& renderer)const override;
	void cameraInput();
	void chaseCamera();
	void fadeInCamera();
	void fadeOutCamera();
	void defaultCamera();
	void fadeInFixedCamera();
	void lockCamera();
	void cameraSet();
	void toPlayerCamera();
	void toBookCamera();
	void toFixedCamera();

	Vector3 accessCorrection(Vector3 pos);
	virtual void onMessage(const std::string& message, void* parameter) override;

private:
	float m_progress = 0.0f;
	bool isMove = false;
	CameraState m_cameraState;
	CameraMatrix m_cameraMatrix;
	std::weak_ptr<BaseActor> m_actor;
	bool m_onCompleted; 
	float m_actorRadius;
	Optional<Vector3> m_lockPos;
};
