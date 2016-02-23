# include "Instant.h"

# include "Gimmick/GimmickManager.h"
# include "Utility/Math.h"

# include "Actor/Particle/LightParticleGenerator.h"
# include "Manager/MessageManager.h"

Instant::Instant(IWorld& world, const std::string& name, const Vector3& position, const std::vector<std::string>& parameter)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 5.0f))
	, m_isGravity(true)
	, m_isActive(true)
	, m_message(none)
{
	for (auto&& param : parameter)
	{
		if (param == "IsKinematic")
		{
			m_isGravity = false;
		}
		if (param == "NonActivate")
		{
			m_isActive = false;
		}
		if (param.find("Message") != std::string::npos)
		{
			m_message = String::Split(param, ':')[1];
		}
		if (param.find("Accessory") != std::string::npos)
		{
			m_accessory = String::Split(param, ':')[1];
		}
	}

	auto particleSystem = std::make_shared<LightParticleGenerator>(*m_world, getPosition(), static_cast<Sphere*>(getShape())->radius);
	m_particleSystem = particleSystem;
	this->addChild(particleSystem);
}

void Instant::onUpdate()
{
	if (m_isActive)
	{
		m_pose.position.y -= m_isGravity ? 2.0f : 0.0f;
	}
	BaseActor::onUpdate();
}

void Instant::onDraw(Renderer& renderer) const
{
	if (m_isActive)
	{
		renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	}
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

	if (message == "Activate")
	{
		m_isActive = true;
		m_particleSystem.lock()->sendMessage("Wake", nullptr);
	}

	if (message == "SubPoint")
	{
		GimmickManager::add(-1);
	}

	BaseActor* actor = static_cast<BaseActor*>(parameter);
	if (m_isActive &&
		!isDead() &&
		message == "onCollide" &&
		actor->getName() == "Player")
	{
		kill();
		if (auto particleSystem = m_particleSystem.lock())
		{
			particleSystem->sendMessage("kill", nullptr);
		}
		GimmickManager::add(1);

		if (m_message)
		{
			MessageManager::Add(m_message.ref());
			MessageManager::SetShow(true);
			m_message = none;
		}

		if (m_accessory)
		{
			m_world->findGroup(ActorTag::Environment)
				->find("Accessory")->sendMessage("VisibleAccessory", &m_accessory.ref());
		}
	}

	return BaseActor::onMessage(message, parameter);
}
