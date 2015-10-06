# pragma once

# include "IShape.h"

class Capsule : public IShape
{
public:

	Capsule(const VECTOR& origin, const VECTOR& end, float radius);

	virtual bool Intersects(Sphere* shape) const override;

	virtual bool Intersects(Capsule* shape) const override;

	virtual bool Intersects(Line* shape) const override;

	virtual bool Intersects(Triangle* shape) const override;

public:

	VECTOR end;

	float radius;
};
