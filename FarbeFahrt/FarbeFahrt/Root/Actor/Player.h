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
	Player(IWorld& world, const VECTOR position);
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
private:
	void playerInput();//入力系（ただの関数分け）
private:
	PlayerState state;
	float moveSpeed;
	bool moveFlag;
	Capsule capsule;
};
