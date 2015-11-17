# pragma once

# include "Actor/BaseActor.h"

class Page : public BaseActor
{
public:

	Page(IWorld& world, const String& name, const Vector3& position,
		const String& backgroundName, const String& groundName, bool isOpen);
};
