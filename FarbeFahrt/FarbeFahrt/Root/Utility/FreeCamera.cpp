# include "FreeCamera.h"

# include "Matrix.h"

FreeCamera::FreeCamera()
{
	// SetCameraNearFar(0.1f, 1000.0f);
}

void FreeCamera::setPosition(const Vector3& position)
{
	m_position = position;
}

void FreeCamera::setDirection(const Vector3& direction)
{
	m_direction = direction;
}

void FreeCamera::move(const Vector3& translation)
{
	m_position += translation;
}

void FreeCamera::rotate(const Vector3& axis, double angle)
{
	m_direction = Vector3::Rotate(m_direction, axis, angle);
}

void FreeCamera::lookAt(const Vector3& target)
{
	m_direction = target - m_position;
}

void FreeCamera::apply() const
{
	Matrix view = Matrix::LookAt(
			m_position, m_position + m_direction, Vector3::Up());
	SetCameraViewMatrix(view);
}

Vector3 FreeCamera::right() const
{
	return Vector3::Normalize(Vector3::Cross(Vector3::Up(), forward()));
}

Vector3 FreeCamera::up() const
{
	return Vector3::Cross(forward(), right());
}

Vector3 FreeCamera::forward() const
{
	return Vector3::Normalize(m_direction);
}
