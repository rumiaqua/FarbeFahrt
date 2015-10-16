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

	virtual bool intersects(const IShape* shape) const = 0;

	virtual bool intersects(const Sphere* shape) const = 0;

	virtual bool intersects(const Capsule* shape) const = 0;

	virtual bool intersects(const Line* shape) const = 0;

	virtual bool intersects(const Triangle* shape) const = 0;

	virtual void draw() const = 0;

public:

	VECTOR origin;
};
