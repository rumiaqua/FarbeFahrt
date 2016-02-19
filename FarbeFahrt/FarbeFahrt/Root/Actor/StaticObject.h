#pragma once
#include "BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class StaticObject :
	public BaseActor
{
public:
	StaticObject(IWorld& world,const std::string& modelName,const Vector3& position);
	StaticObject(IWorld& world, const std::string& modelName, const Vector3& position, float angle, float scale);
private:
	virtual void onDraw(Renderer& renderer)const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:
	float m_scale;
	bool m_isVisible;
};
