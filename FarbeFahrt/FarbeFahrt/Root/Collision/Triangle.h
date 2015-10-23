# pragma once

# include "IShape.h"

class Triangle : public IShape
{
public:

	Triangle(const Vector3& p0, const Vector3& p1, const Vector3& p2);

	virtual bool intersects(const IShape& shape) const override;

	virtual bool intersects(const Sphere& shape) const override;

	virtual bool intersects(const Capsule& shape) const override;

	virtual bool intersects(const Line& shape) const override;

	virtual bool intersects(const Triangle& shape) const override;

	virtual void draw() const override;

public:

	Vector3 p1;

	Vector3 p2;
};
