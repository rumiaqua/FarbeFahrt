# pragma once

# include "Actor/BaseActor.h"

class CameraBookmark : public BaseActor
{
public:

	CameraBookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& actionName);

private:

	virtual void onDraw(Renderer& renderer) const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:

	std::string m_actionName;
	bool m_once;
};
