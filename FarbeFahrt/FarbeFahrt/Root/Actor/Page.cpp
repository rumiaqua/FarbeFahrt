# include "Page.h"

# include "Actor/SkinObject.h"

# include "Utility/Math.h"

Page::Page(IWorld& world, const String& name, const Vector3& position, const String& backgroundName, const String& groundName, bool isOpen)
	: BaseActor(world, name, position, Matrix::Rotation(Vector3::Up(), Math::ToRadian(Math::PI)), nullptr)
{
	int animNo = isOpen ? 0 : 1;
	addChild(std::make_shared<SkinObject>(world, backgroundName, Vector3::Zero(), animNo, 0.1f, 589.0f));
	addChild(std::make_shared<SkinObject>(world, groundName, Vector3::Zero(), animNo, 0.1f, 589.0f));
}
