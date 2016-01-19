# include "Instant.h"

# include "Gimmick/GimmickManager.h"
# include "Utility/Math.h"

Instant::Instant(IWorld& world, const std::string& name, const Vector3& position)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 5.0f))
	, m_isGravity(true)
{

}

void Instant::onUpdate()
{
	m_pose.position.y -= m_isGravity ? 2.0f : 0.0f;
	BaseActor::onUpdate();
}

void Instant::onDraw(Renderer& renderer) const
{
	renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	BaseActor::onDraw(renderer);
}

void Instant::onMessage(const std::string& message, void* parameter)
{
	if (message == "HitGround" &&
		m_isGravity)
	{
		Vector3* pos = static_cast<Vector3*>(parameter);
		m_pose.position = *pos;
	}

	if (message == "Fall")
	{
		m_isGravity = true;
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