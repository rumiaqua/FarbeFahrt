#include "PlayerSpawner.h"
# include "Utility/Input.h"
# include "Player.h"

PlayerSpawner::PlayerSpawner(IWorld& world, const Vector3& position, const std::vector<Vector4>& noEntries)
	: BaseActor(world, "PlayerSpawner", position, Matrix::identity(), nullptr)
	, m_isActive(true)
	, m_noEntries(noEntries)
{

}

void PlayerSpawner::onMessage(const std::string& message, void* parameter)
{
	if (m_isActive && message == "PlayerSpawn")
	{
		m_world->addActor(ActorTag::Player, std::make_shared<Player>(*m_world, getPosition(), m_noEntries));
		m_isActive = false;
	}

	BaseActor::onMessage(message, parameter);
}
