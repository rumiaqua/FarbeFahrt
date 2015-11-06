# pragma once

# include "IShape.h"

class Line : public IShape
{
public:

	Line(const Vector3& begin, const Vector3& end);

	virtual bool intersects(const IShape& shape) const override;

	virtual bool intersects(const Sphere& shape) const override;

	virtual bool intersects(const Capsule& shape) const override;

	virtual bool intersects(const Line& shape) const override;

	virtual bool intersects(const Triangle& shape) const override;

	virtual void draw() const override;

public:

	Vector3 begin;
	Vector3 end;
};
