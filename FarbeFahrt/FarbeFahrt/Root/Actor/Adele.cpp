#include "Adele.h"
#include "Actor/Particle/LightParticleGenerator.h"

# include "Utility/Math.h"
# include "Gimmick\GimmickManager.h"
# include "Scene\Scene.h"
Adele::Adele(IWorld& world, const std::string& name, const Vector3& position, ISceneMediator* manager)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 3.0f))
	, m_isCollide(false)
{
	m_manager = manager;

	auto particleSystem = std::make_shared<LightParticleGenerator>(*m_world, getPosition(), static_cast<Sphere*>(getShape())->radius);
	m_particleSystem = particleSystem;
	this->addChild(particleSystem);
	m_particleSystem.lock()->sendMessage("Wake", nullptr);
}

void Adele::onMessage(const std::string& message, void* parameter)
{

	BaseActor* actor = static_cast<BaseActor*>(parameter);
	if (!isDead() &&
		message == "onCollide" &&
		actor->getName() == "Player")
	{
		m_isCollide = true;
		actor->sendMessage("RideOn", nullptr);
		m_manager->pushScene(Scene::BlackOut, 60.0f);
		if (auto particleSystem = m_particleSystem.lock())
		{
			particleSystem->sendMessage("kill", nullptr);
		}
		kill();

		GimmickManager::add(1);
	}

	BaseActor::onMessage(message, parameter);
}
