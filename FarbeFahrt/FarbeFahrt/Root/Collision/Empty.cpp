# include "Empty.h"

Empty::Empty()
{

}

bool Empty::intersects(const IShape& shape) const
{
	return false;
}

bool Empty::intersects(const Sphere& shape) const
{
	return false;
}

bool Empty::intersects(const Capsule& shape) const
{
	return false;
}

bool Empty::intersects(const Line& shape) const
{
	return false;
}

bool Empty::intersects(const Triangle& shape) const
{
	return false;
}

bool Empty::intersects(const ModelCollider& shape) const
{
	return false;
}

bool Empty::intersects(const Empty& shape) const
{
	return false;
}

void Empty::draw() const
{
	
}
