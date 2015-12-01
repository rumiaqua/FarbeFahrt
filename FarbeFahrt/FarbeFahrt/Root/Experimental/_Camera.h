# pragma once

# include "Actor/BaseActor.h"

class _Camera : public BaseActor
{
public:

	_Camera(IWorld& world);

private:

	void actorSet(const std::string& name);

private:

	virtual void onUpdate() override;
	virtual void onDraw(Renderer& renderer) const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:

	float m_elapsedTime;
	bool m_isMove;
	std::weak_ptr<BaseActor> m_actor;
	bool m_onCompleted;
};
