# pragma once

# include "IShape.h"
# include "Utility\String.h"
class ModelCollider : public IShape
{
public:

	ModelCollider(const String& name);

	virtual bool intersects(const IShape& shape) const override;

	virtual bool intersects(const Sphere& shape) const override;

	virtual bool intersects(const Capsule& shape) const override;

	virtual bool intersects(const Line& shape) const override;

	virtual bool intersects(const Triangle& shape) const override;

	virtual void draw() const override;

public:

	String name;
};
