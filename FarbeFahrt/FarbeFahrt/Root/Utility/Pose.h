# pragma once

# include "Vector3.h"

# include "Matrix.h"

class Pose
{
public:

	Pose();

	Pose(const Vector3& position, const Matrix& matrix);

	Matrix getPose() const;

	Vector3& getPosition();

	const Vector3& getPosition() const;

	Matrix& getRotation();

	const Matrix& getRotation() const;

public:

	Vector3 position;

	Matrix rotation;
};
