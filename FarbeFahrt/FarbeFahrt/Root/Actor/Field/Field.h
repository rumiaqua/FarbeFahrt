#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
#include "Experimental/AnimationTransitionMachine.h"
#include "Actor/Camera/Camera.h"

struct AnimateState;

class Field :
	public BaseActor
{
public:
	explicit Field(IWorld& world, const std::string& name, const Vector3& position, float scale, const std::string& transition);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& renderer)const override;
	virtual void onMessage(const std::string& message, void* parameter) override;
private:
	void workGimmick(int commandNo);
	bool isGround();
	void animateProcess(const AnimateState& state);
private:
	float m_scale;
	float m_elapsedTime;
	int m_animationNumber;
	bool m_isAnimating;
	bool m_gimmick;
	bool m_isReversed;
	int m_previousAnimNo;
	bool m_isBackground;
	AnimationTransitionMachine m_machine;
	std::string m_current;
	float m_cameraProgress;
};
