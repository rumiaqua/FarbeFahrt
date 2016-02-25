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
	Player(IWorld& world, const Vector3& position, const std::vector<Vector4>& canEntries);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& renderer)const override;	
	virtual void onMessage(const std::string& message, void* parameter) override;
private:
	Vector3 playerInput();//“ü—ÍŒni‚½‚¾‚ÌŠÖ”•ª‚¯j
	void animate(const Vector3& moveVec);
private:
	PlayerState m_state;
	float m_moveSpeed;
	bool m_moveFlag;
	float m_frame;

	bool m_canControl;
	float m_previousFrame;

	Vector3 m_previousPosition;

	std::vector<Vector4> m_noEntries;
};
