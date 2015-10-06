# pragma once

# include <DxLib.h>

class Sphere;
class Capsule;
class Line;
class Triangle;

class IShape
{
public:

	IShape(const VECTOR& origin);

	virtual ~IShape();

	virtual bool Intersects(Sphere* shape) const = 0;

	virtual bool Intersects(Capsule* shape) const = 0;

	virtual bool Intersects(Line* shape) const = 0;

	virtual bool Intersects(Triangle* shape) const = 0;

public:

	VECTOR origin;
};
