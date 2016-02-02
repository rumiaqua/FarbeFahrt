# pragma once

# include "IShape.h"

class Sphere : public IShape
{
public:

	Sphere(const Vector3& center, float radius);

	virtual bool intersects(const IShape& shape) const override;
	virtual bool intersects(const Sphere& shape) const override;
	virtual bool intersects(const Capsule& shape) const override;
	virtual bool intersects(const Line& shape) const override;
	virtual bool intersects(const Triangle& shape) const override;
	virtual bool intersects(const ModelCollider& shape) const override;
	virtual bool intersects(const Empty& shape) const override;

	virtual void draw() const override;

public:

	Vector3 center;

	float radius;
};
