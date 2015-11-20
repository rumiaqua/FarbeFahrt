# include "FreeCamera.h"

# include "Matrix.h"

FreeCamera::FreeCamera()
	: m_position()
	, m_direction(Vector3::Forward())
	, m_up(Vector3::Up())
{

}

void FreeCamera::setPosition(const Vector3& position)
{
	m_position = position;
}

void FreeCamera::setDirection(const Vector3& direction)
{
	m_direction = direction;
	m_up = Vector3::Cross(m_direction, Vector3::Cross(m_up, m_direction));
}

void FreeCamera::move(const Vector3& translation)
{
	m_position += translation;
}

void FreeCamera::rotate(const Vector3& axis, double angle)
{
	m_direction = Vector3::Rotate(m_direction, axis, angle);
	m_up = Vector3::Rotate(m_up, axis, angle);
}

void FreeCamera::lookAt(const Vector3& target)
{
	m_direction = target - m_position;
	m_up = Vector3::Cross(m_direction, Vector3::Cross(m_up, m_direction));
}

void FreeCamera::apply() const
{
	Matrix view = Matrix::LookAt(
			m_position, m_position + m_direction, m_up);
	SetCameraViewMatrix(view);
}

Vector3 FreeCamera::right() const
{
	return Vector3::Normalize(Vector3::Cross(up(), forward()));
}

Vector3 FreeCamera::up() const
{
	return Vector3::Normalize(m_up);
}

Vector3 FreeCamera::forward() const
{
	return Vector3::Normalize(m_direction);
}
