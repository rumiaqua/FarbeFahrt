# include "ModelCollider.h"

# include "Collision.h"

# include "Utility/SingletonFinalizer.h"
# include "Utility/HandleList.h"

# include <DxLib.h>

ModelCollider::ModelCollider(const String& name)
	: name(name)
{

}

bool ModelCollider::intersects(const IShape& shape) const
{
	return shape.intersects(*this);
}

bool ModelCollider::intersects(const Sphere& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const Capsule& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const Line& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const Triangle& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const ModelCollider& shape) const
{
	// ƒ‚ƒfƒ‹‚Æƒ‚ƒfƒ‹‚ÌÕ“Ë”»’è‚Í‚µ‚È‚¢•ûŒü«‚Å
	NoUse(shape);
	return false;
}

void ModelCollider::draw() const
{
	MV1DrawModelDebug(Singleton<HandleList>::Instance().getHandle(name),
		(unsigned int)-1, FALSE, 0.0f, TRUE, FALSE);
}
