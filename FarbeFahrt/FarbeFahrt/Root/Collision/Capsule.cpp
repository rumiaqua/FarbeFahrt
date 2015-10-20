# include "Capsule.h"

# include "Collision.h"

# include <DxLib.h>

# include "Utility/MemoryCast.h"

Capsule::Capsule(const Vector3& origin, const Vector3& end, float radius)
	: IShape(origin)
	, end(end)
	, radius(radius)
{

}

bool Capsule::intersects(const IShape* shape) const
{
	return shape->intersects(this);
}

bool Capsule::intersects(const Sphere* shape) const
{
	return Collision::intersects(this, shape);
}

bool Capsule::intersects(const Capsule* shape) const
{
	return Collision::intersects(this, shape);
}

bool Capsule::intersects(const Line* shape) const
{
	return Collision::intersects(this, shape);
}

bool Capsule::intersects(const Triangle* shape) const
{
	return Collision::intersects(this, shape);
}

void Capsule::draw() const
{
	DrawCapsule3D(
		memory_cast<VECTOR>(origin),
		memory_cast<VECTOR>(end),
		radius, 10, -1, -1, FALSE);
}
