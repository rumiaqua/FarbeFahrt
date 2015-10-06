# pragma once

# include "IShape.h"

class Triangle : public IShape
{
public:

	Triangle(const VECTOR& p0, const VECTOR& p1, const VECTOR& p2);

	virtual bool Intersects(Sphere* shape) const override;

	virtual bool Intersects(Capsule* shape) const override;

	virtual bool Intersects(Line* shape) const override;

	virtual bool Intersects(Triangle* shape) const override;

public:

	VECTOR p1;

	VECTOR p2;
};
