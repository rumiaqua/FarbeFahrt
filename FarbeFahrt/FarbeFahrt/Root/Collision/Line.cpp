#include "Line.h"

# include "Collision.h"

# include <DxLib.h>

# include "Utility/MemoryCast.h"

Line::Line(const Vector3& begin, const Vector3& end)
	: begin(begin)
	, end(end)
{

}

bool Line::intersects(const IShape& shape) const
{
	return shape.intersects(*this);
}

bool Line::intersects(const Sphere& shape) const
{
	return Collision::intersects(*this, shape);
}

bool Line::intersects(const Capsule& shape) const
{
	return Collision::intersects(*this, shape);
}

bool Line::intersects(const Line& shape) const
{
	return Collision::intersects(*this, shape);
}

bool Line::intersects(const Triangle& shape) const
{
	return Collision::intersects(*this, shape);
}

void Line::draw() const
{
	DrawLine3D(
		origin + begin,
		origin + end,
		-1);
}
