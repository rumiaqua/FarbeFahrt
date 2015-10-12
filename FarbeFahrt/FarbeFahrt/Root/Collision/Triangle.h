# pragma once

# include "IShape.h"

class Triangle : public IShape
{
public:

	Triangle(const VECTOR& p0, const VECTOR& p1, const VECTOR& p2);

	virtual bool intersects(const IShape* shape) const override;

	virtual bool intersects(const Sphere* shape) const override;

	virtual bool intersects(const Capsule* shape) const override;

	virtual bool intersects(const Line* shape) const override;

	virtual bool intersects(const Triangle* shape) const override;

	virtual void draw() const override;

public:

	VECTOR p1;

	VECTOR p2;
};
