#include "PlayerSpawner.h"
# include "Utility/Input.h"
# include "Player.h"

PlayerSpawner::PlayerSpawner(IWorld& world, const Vector3& position)
	: BaseActor(world, "PlayerSpawner", position, Matrix::identity(), nullptr)
	, m_isActive(true)
{

}

void PlayerSpawner::onUpdate()
{
	if (!m_isActive)
	{
		return;
	}

	// ƒeƒXƒg
	// onMessage("PlayerSpawn", nullptr);
}

void PlayerSpawner::onMessage(const String& message, void* parameter)
{
	if (m_isActive && message == "PlayerSpawn")
	{
		m_world->addActor(ActorTag::Player, std::make_shared<Player>(*m_world, getPosition()));
		m_isActive = false;
	}

	BaseActor::onMessage(message, parameter);
}
