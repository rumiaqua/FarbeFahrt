# pragma once

# include "IShape.h"

class ModelCollider : public IShape
{
public:

	ModelCollider(int handle);

	virtual bool intersects(const IShape& shape) const override;

	virtual bool intersects(const Sphere& shape) const override;

	virtual bool intersects(const Capsule& shape) const override;

	virtual bool intersects(const Line& shape) const override;

	virtual bool intersects(const Triangle& shape) const override;

	virtual void draw() const override;

public:

	int handle;
};
