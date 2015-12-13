#pragma once
#include "Actor/BaseActor.h"
#include "Utility/Def.h"
class Field :
	public BaseActor
{
public:
	explicit Field(IWorld& world, const std::string& name, const Vector3& position, float scale);
public:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	virtual void onMessage(const std::string& message, void* parameter) override;
private:
	void open();
	void close();
	void reverseOpen();
private:
	float m_scale;
	float m_elapsedTime;
	int m_animationNumber;
	bool m_isAnimating;
	bool m_isReversed;
};
