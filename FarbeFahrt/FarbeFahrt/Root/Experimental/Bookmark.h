# pragma once

# include "Actor/BaseActor.h"
# include "Collision/Capsule.h"
# include "Utility/String.h"

class Bookmark : public BaseActor
{
public:

	Bookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& parameter);

private:

	virtual void onDraw(Renderer& renderer) const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:
	
	int m_addPoint;
	bool m_isAddPoint;
	bool m_isToggle;
	std::string m_animateName;
	Vector3 m_access;
	bool m_isActive;
};
