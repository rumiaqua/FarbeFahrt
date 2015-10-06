# pragma once

# include "IShape.h"

class Sphere : public IShape
{
public:

	Sphere(const VECTOR& origin, float radius);

	virtual bool Intersects(Sphere* shape) const override;

	virtual bool Intersects(Capsule* shape) const override;

	virtual bool Intersects(Line* shape) const override;

	virtual bool Intersects(Triangle* shape) const override;

public:

	float radius;
};
