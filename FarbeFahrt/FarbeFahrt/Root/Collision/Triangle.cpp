# include "Triangle.h"

# include "Collision.h"

Triangle::Triangle(const VECTOR& p0, const VECTOR& p1, const VECTOR& p2)
	: IShape(p0)
	, p1(p1)
	, p2(p2)
{

}

bool Triangle::intersects(const IShape* shape) const
{
	return shape->intersects(this);
}

bool Triangle::intersects(const Sphere* shape) const
{
	return Collision::intersects(this, shape);
}

bool Triangle::intersects(const Capsule* shape) const
{
	return Collision::intersects(this, shape);
}

bool Triangle::intersects(const Line* shape) const
{
	return Collision::intersects(this, shape);
}

bool Triangle::intersects(const Triangle* shape) const
{
	return Collision::intersects(this, shape);
}

void Triangle::draw() const
{
	DrawTriangle3D(origin, p1, p2, -1, FALSE);
}
