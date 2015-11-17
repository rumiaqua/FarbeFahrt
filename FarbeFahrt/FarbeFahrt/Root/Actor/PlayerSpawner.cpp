#include "PlayerSpawner.h"
# include "Utility/Input.h"
# include "Player.h"

PlayerSpawner::PlayerSpawner(IWorld& world, const String& name, const Vector3& position)
	: BaseActor(world, name, position, Matrix::identity(), nullptr)
{

}

void PlayerSpawner::onUpdate()
{
	//if (Input::IsClicked(KEY_INPUT_0))
	{
		onMessage("PlayerSpawn", nullptr);
	}
}

void PlayerSpawner::onMessage(const String& message, void * parameter)
{
	if (message == "PlayerSpawn")
	{
		m_world->addActor(ActorTag::Player, std::make_shared<Player>(*m_world, getPosition()));
		kill();
	}

	BaseActor::onMessage(message, parameter);
}
