# include "Capsule.h"

# include "Collision.h"

Capsule::Capsule(const VECTOR& origin, const VECTOR& end, float radius)
	: IShape(origin)
	, end(end)
	, radius(radius)
{

}

bool Capsule::Intersects(Sphere* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Capsule::Intersects(Capsule* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Capsule::Intersects(Line* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Capsule::Intersects(Triangle* shape) const
{
	return Collision::Intersects(this, shape);
}
