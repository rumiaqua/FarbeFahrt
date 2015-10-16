# include "Sphere.h"

# include "Collision.h"

Sphere::Sphere(const VECTOR& origin, float radius)
	: IShape(origin)
	, radius(radius)
{

}

bool Sphere::intersects(const IShape* shape) const
{
	return shape->intersects(this);
}

bool Sphere::intersects(const Sphere* shape) const
{
	return Collision::intersects(this, shape);
}

bool Sphere::intersects(const Capsule* shape) const
{
	return Collision::intersects(this, shape);
}

bool Sphere::intersects(const Line* shape) const
{
	return Collision::intersects(this, shape);
}

bool Sphere::intersects(const Triangle* shape) const
{
	return Collision::intersects(this, shape);
}

void Sphere::draw() const
{
	DrawSphere3D(origin, radius, 10, -1, -1, FALSE);
}