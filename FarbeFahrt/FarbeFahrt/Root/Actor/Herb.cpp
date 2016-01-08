#include "Herb.h"

Herb::Herb(IWorld& world, const Vector3& position)
	: BaseActor(world, "Herb", position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 30.0f))
	, m_gravity(0.0f)
{

}

void Herb::onUpdate()
{
	m_pose.position.y -= m_gravity;
}

void Herb::onMessage(const std::string& message, void* parameter)
{
	if (message == "HitGround")
	{
		Vector3* pos = static_cast<Vector3*>(parameter);
		m_pose.position = *pos;
	}

	if (message == "Fall")
	{
		m_gravity = 2.0f;
	}

	return BaseActor::onMessage(message, parameter);
}
