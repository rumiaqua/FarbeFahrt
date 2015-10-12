# pragma once

# include "IShape.h"

class Line : public IShape
{
public:

	Line(const VECTOR& origin, const VECTOR& end);

	virtual bool intersects(const IShape* shape) const override;

	virtual bool intersects(const Sphere* shape) const override;

	virtual bool intersects(const Capsule* shape) const override;

	virtual bool intersects(const Line* shape) const override;

	virtual bool intersects(const Triangle* shape) const override;

	virtual void draw() const override;

public:

	VECTOR end;
};
