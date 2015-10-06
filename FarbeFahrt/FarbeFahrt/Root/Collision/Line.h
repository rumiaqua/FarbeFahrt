# pragma once

# include "IShape.h"

class Line : public IShape
{
public:

	Line(const VECTOR& origin, const VECTOR& end);

	virtual bool Intersects(Sphere* shape) const override;

	virtual bool Intersects(Capsule* shape) const override;

	virtual bool Intersects(Line* shape) const override;

	virtual bool Intersects(Triangle* shape) const override;

public:

	VECTOR end;
};
