# include "Triangle.h"

# include "Collision.h"

# include <DxLib.h>

# include "Utility/MemoryCast.h"

Triangle::Triangle(const Vector3& p0, const Vector3& p1, const Vector3& p2)
	: p0(p0)
	, p1(p1)
	, p2(p2)
{

}

bool Triangle::intersects(const IShape& shape) const
{
	return shape.intersects(*this);
}

bool Triangle::intersects(const Sphere& shape) const
{
	return Collision::intersects(*this, shape);
}

bool Triangle::intersects(const Capsule& shape) const
{
	return Collision::intersects(*this, shape);
}

bool Triangle::intersects(const Line& shape) const
{
	return Collision::intersects(*this, shape);
}

bool Triangle::intersects(const Triangle& shape) const
{
	return Collision::intersects(*this, shape);
}

bool Triangle::intersects(const ModelCollider& shape) const
{
	return Collision::intersects(shape, *this);
}

bool Triangle::intersects(const Empty& shape) const
{
	return false;
}

void Triangle::draw() const
{
	DrawTriangle3D(
		origin + p0,
		origin + p1,
		origin + p2,
		-1, FALSE);
}
