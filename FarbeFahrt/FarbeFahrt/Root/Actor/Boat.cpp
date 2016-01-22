# include "Boat.h"

# include "Utility/Renderer.h"

Boat::Boat(IWorld& world, const std::string& name, const Vector3& position)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 10.0f))
	, m_isActive(false)
{

}

void Boat::onUpdate()
{
	if (m_isActive)
	{
		Vector3 Speed = Vector3::Left() * 2.0f;
		m_pose.position += Speed;
		m_world->findActor("Player")->sendMessage("Translate", &Speed);
	}
	BaseActor::onUpdate();
}

void Boat::onDraw(Renderer& renderer) const
{
	// renderer.setScale(m_name, { 3.0f, 3.0f, 3.0f });
	// renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	BaseActor::onDraw(renderer);
}

void Boat::onMessage(const std::string& message, void* parameter)
{
	if (message == "Activate")
	{
		m_isActive = true;
		m_world->findActor("Player")->sendMessage("StopControl", nullptr);
	}

	return BaseActor::onMessage(message, parameter);
}
