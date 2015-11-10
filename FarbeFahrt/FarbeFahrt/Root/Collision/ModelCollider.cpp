# include "ModelCollider.h"

# include "Collision.h"

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

void ModelCollider::draw() const
{

}
