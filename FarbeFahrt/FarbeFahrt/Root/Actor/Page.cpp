# include "Page.h"

# include "Actor/SkinObject.h"

# include "Utility/Math.h"

Page::Page(IWorld& world, const std::string& name, const Vector3& position, const std::string& backgroundName, const std::string& groundName, bool isOpen, float scale, float angle)
	: BaseActor(world, name, position, Matrix::Rotation(Vector3::Up(), Math::ToRadian(Math::PI)), nullptr)
{
	int animNo = isOpen ? 0 : 1;
	addChild(std::make_shared<SkinObject>(world, backgroundName, Vector3::Zero(), animNo, 1.0f, 59.0f, scale, angle, false));
	addChild(std::make_shared<SkinObject>(world, groundName, Vector3::Zero(), animNo, 1.0f, 59.0f, scale, angle, false));
}
