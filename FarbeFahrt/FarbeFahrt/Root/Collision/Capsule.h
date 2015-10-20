# pragma once

# include "IShape.h"

class Capsule : public IShape
{
public:

	Capsule(const Vector3& origin, const Vector3& end, float radius);

	virtual bool intersects(const IShape* shape) const override;

	virtual bool intersects(const Sphere* shape) const override;

	virtual bool intersects(const Capsule* shape) const override;

	virtual bool intersects(const Line* shape) const override;

	virtual bool intersects(const Triangle* shape) const override;

	virtual void draw() const override;

public:

	Vector3 end;

	float radius;
};
