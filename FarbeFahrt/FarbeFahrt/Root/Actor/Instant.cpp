# include "Instant.h"

# include "Gimmick/GimmickManager.h"

Instant::Instant(IWorld& world, const std::string& name, const Vector3& position)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 30.0f))
	, m_gravity(0.0f)
{

}

void Instant::onUpdate()
{
	m_pose.position.y -= m_gravity;
}

void Instant::onMessage(const std::string& message, void* parameter)
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

	BaseActor* actor = static_cast<BaseActor*>(parameter);
	if (!isDead() &&
		message == "onCollide" &&
		actor->getName() == "Player")
	{
		kill();
		GimmickManager::add(1);
	}

	return BaseActor::onMessage(message, parameter);
}
