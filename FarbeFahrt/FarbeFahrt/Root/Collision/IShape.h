# pragma once

# include "Utility/Vector3.h"

class Sphere;
class Capsule;
class Line;
class Triangle;

class IShape
{
public:

	IShape(const Vector3& origin);

	virtual ~IShape();

	virtual bool intersects(const IShape& shape) const = 0;

	virtual bool intersects(const Sphere& shape) const = 0;

	virtual bool intersects(const Capsule& shape) const = 0;

	virtual bool intersects(const Line& shape) const = 0;

	virtual bool intersects(const Triangle& shape) const = 0;

	virtual void draw() const = 0;

public:

	Vector3 origin;
};
