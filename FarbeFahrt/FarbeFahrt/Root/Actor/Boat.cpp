# include "Boat.h"

# include "Utility/Renderer.h"

Boat::Boat(IWorld& world, const std::string& name, const Vector3& position)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3(0.0f, 0.0f, -25.0f), 10.0f))
	, m_isActive(false)
	, m_player()
	, m_delay(120.0f)
{

}

void Boat::onUpdate()
{
	if (m_isActive)
	{
		if ((m_delay -= 1.0f) < 0.0f)
		{
			Vector3 Speed = Vector3::Right() * 1.0f;
			m_pose.position += Speed;
			if (!m_player.expired())
			{
				// m_player->sendMessage("Translate", &Speed);
				Vector3 position = getPosition() + m_relative;
				m_player.lock()->sendMessage("SetPosition", &position);
			}
		}
	}

	/*
	const float XLim = 142.0f;
	const float ZLim = 110.0f;
	const float Correction = 145.0f / 2.0f - 4.0f;
	*/
	const float Limit = 142.0f - (145.0f / 2.0f - 4.0f);
	if (m_pose.position.x > Limit)
	{
		m_pose.position.x = Limit;
	}

	BaseActor::onUpdate();
}

void Boat::onDraw(Renderer& renderer) const
{
	renderer.setScale(m_name, { 4.0f, 4.0f, 4.0f });
	renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	BaseActor::onDraw(renderer);
}

void Boat::onMessage(const std::string& message, void* parameter)
{
	if (message == "Activate")
	{
		m_isActive = true;
		bool isKill = false;
		if (auto player = m_world->findActor("Player"))
		{
			if (this->isCollide(player.get()))
			{
				m_player = player;
				m_player.lock()->sendMessage("StopControl", &isKill);
				m_relative = player->getPosition() - getPosition();
			}
		}
	}

	return BaseActor::onMessage(message, parameter);
}
