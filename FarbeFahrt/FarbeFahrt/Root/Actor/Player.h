#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"

enum class PlayerState
{
	standing = 0,
	walking,
	Bwalking,
	jumping
};
class Player :
	public BaseActor
{
public:
	Player(IWorld& world, const Vector3& position);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;	
	virtual void onMessage(const String& message, void* parameter) override;
private:
	void playerInput();//“ü—ÍŒni‚½‚¾‚ÌŠÖ”•ª‚¯j
private:
	PlayerState m_state;
	float m_moveSpeed;
	bool m_moveFlag;
	float m_frame;

	bool m_canControl;
};
