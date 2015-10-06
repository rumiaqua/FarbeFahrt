# include "Sphere.h"

# include "Collision.h"

Sphere::Sphere(const VECTOR& origin, float radius)
	: IShape(origin)
	, radius(radius)
{

}

bool Sphere::Intersects(Sphere* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Sphere::Intersects(Capsule* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Sphere::Intersects(Line* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Sphere::Intersects(Triangle* shape) const
{
	return Collision::Intersects(this, shape);
}
