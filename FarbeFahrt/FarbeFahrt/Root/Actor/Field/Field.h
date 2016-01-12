#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
#include "Experimental/AnimationTransitionMachine.h"

struct AnimateState;

class Field :
	public BaseActor
{
public:
	explicit Field(IWorld& world, const std::string& name, const Vector3& position, float scale, const std::string& transition);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	virtual void onMessage(const std::string& message, void* parameter) override;
private:
	void open();
	void close();
	void reverseOpen();
	void openShop();
	void animateProcess(const AnimateState& state);
private:
	float m_scale;
	float m_elapsedTime;
	int m_animationNumber;
	bool m_isAnimating;
	bool m_isReversed;
	bool m_isBackground;
	AnimationTransitionMachine m_machine;
};
