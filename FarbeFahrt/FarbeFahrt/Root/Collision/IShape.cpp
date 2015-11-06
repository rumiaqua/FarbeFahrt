# include "IShape.h"
# include "Utility/Matrix.h"

IShape::IShape()
	: origin(Vector3::Zero())
{

}

IShape::~IShape()
{

}

IShape* const IShape::transform(const Matrix& pose)
{
	this->origin = Matrix::Translation(pose);
	return this;
}
