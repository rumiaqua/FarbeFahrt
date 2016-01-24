# pragma once

# include "Actor/BaseActor.h"

class ActionBookmark : public BaseActor
{
public:

	ActionBookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& targetName, const std::string& actionName);

private:

	virtual void onDraw(Renderer& renderer) const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:

	std::string m_targetName;
	std::string m_actionName;
	bool m_once;
};
