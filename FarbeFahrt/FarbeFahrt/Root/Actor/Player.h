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
	virtual void onMessage(const String& message, const void* parameter) override;
private:
	void playerInput();//入力系（ただの関数分け）
private:
	PlayerState m_state;
	float m_moveSpeed;
	bool m_moveFlag;
	float m_flame;
};
