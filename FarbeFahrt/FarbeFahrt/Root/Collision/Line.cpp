#include "Line.h"

# include "Collision.h"

Line::Line(const VECTOR& origin, const VECTOR& end)
	: IShape(origin)
	, end(end)
{

}

bool Line::Intersects(Sphere* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Line::Intersects(Capsule* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Line::Intersects(Line* shape) const
{
	return Collision::Intersects(this, shape);
}

bool Line::Intersects(Triangle* shape) const
{
	return Collision::Intersects(this, shape);
}
