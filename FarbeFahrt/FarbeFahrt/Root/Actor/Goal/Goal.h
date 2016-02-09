#pragma once
#include "Actor/BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class Goal :
	public BaseActor
{
public:
	Goal(IWorld& world, const std::string& modelName, const Vector3& position, int threshold);
private:
	virtual void onDraw(Renderer& renderer)const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:
	int m_threshold;
};
