# pragma once

# include "Actor/BaseActor.h"

class Page : public BaseActor
{
public:

	Page(IWorld& world, const std::string& name, const Vector3& position,
		const std::string& backgroundName, const std::string& groundName, bool isOpen, float scale, float angle);
};
