# include "Triangle.h"

# include "Collision.h"

Triangle::Triangle(const VECTOR& p0, const VECTOR& p1, const VECTOR& p2)
	: IShape(p0)
	, p1(p1)
	, p2(p2)
{

}

 bool Triangle::Intersects(Sphere* shape) const
{
	return Collision::Intersects(this, shape);
}

 bool Triangle::Intersects(Capsule* shape) const
 {
	 return Collision::Intersects(this, shape);
 }

 bool Triangle::Intersects(Line* shape) const
 {
	 return Collision::Intersects(this, shape);
 }

 bool Triangle::Intersects(Triangle* shape) const
 {
	 return Collision::Intersects(this, shape);
 }
 