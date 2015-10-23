#include "Pose.h"

Pose::Pose()
	: position()
	, rotation()
{

}

Pose::Pose(const Vector3& position, const Matrix& matrix)
	: position(position)
	, rotation(rotation)
{

}

Matrix Pose::getPose() const
{
	return Matrix::translation(position) * rotation;
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
