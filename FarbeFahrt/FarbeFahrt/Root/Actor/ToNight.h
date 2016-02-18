# pragma once

# include "BaseActor.h"

class ISceneMediator;

class ToNight : public BaseActor
{
public:
	ToNight(IWorld& world, const std::string& name, const Vector3& position, ISceneMediator* mediator);

public:
	virtual void onMessage(const std::string& message, void* parameter) override;
private:
	ISceneMediator* m_mediator;
};
