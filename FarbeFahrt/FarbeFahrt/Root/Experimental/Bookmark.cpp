# include "Bookmark.h"

# include "Actor/Gimmick/GimmickManager.h"

# include "Utility/Math.h"

# include "Experimental/AnimateState.h"

Bookmark::Bookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& animateName, bool once)
	: BaseActor(
		world,
		modelName,
		position,
		Matrix::Rotation(Vector3::Up(),
		Math::HALF_PI),
		std::make_unique<Sphere>(Vector3::Zero(), 3.0f))
	, m_once(once)
	, m_animateName(animateName)
{
	
}

void Bookmark::onMessage(const std::string& message, void* parameter)
{
	if (message == "OnGimmick")
	{
		if (!m_once)
		{
			GimmickManager::add(1);
			m_once = true;
		}
		AnimateState state { m_animateName, false };
		m_world->findGroup(ActorTag::Field)
			->sendMessage("Animate", &state);
	}

	BaseActor::onMessage(message, parameter);
}
