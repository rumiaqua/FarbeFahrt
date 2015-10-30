#include "Pose.h"

Pose::Pose()
	: position()
	, rotation()
{

}

Pose::Pose(const Vector3& position, const Matrix& matrix)
	: position(position)
	, rotation(matrix)
{

}

Matrix Pose::getPose() const
{
	return rotation * Matrix::translation(position);
}

Vector3& Pose::getPosition()
{
	return position;
}

const Vector3& Pose::getPosition() const
{
	return position;
}

Matrix& Pose::getRotation()
{
	return rotation;
}

const Matrix& Pose::getRotation() const
{
	return rotation;
}
