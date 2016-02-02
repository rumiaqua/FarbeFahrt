# pragma once

# include "Actor/BaseActor.h"
# include "Collision/Capsule.h"
# include "Utility/String.h"

class Bookmark : public BaseActor
{
public:

	Bookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& animateName, bool isAddPoint, bool isToggle);

private:

	virtual void onDraw(Renderer& renderer) const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:

	std::string m_animateName;
	bool m_isAddPoint;
	bool m_isToggle;
	int m_addPoint;
};
