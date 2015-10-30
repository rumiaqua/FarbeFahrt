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
	
private:
	void playerInput();//“ü—ÍŒni‚½‚¾‚ÌŠÖ”•ª‚¯j
private:
	PlayerState state;
	float moveSpeed;
	bool moveFlag;
	Capsule capsule;

	Actor stand;
};
