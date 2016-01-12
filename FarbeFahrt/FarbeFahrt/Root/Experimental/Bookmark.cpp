# include "Bookmark.h"

# include "Actor/Gimmick/GimmickManager.h"

# include "Utility/Math.h"

# include "Experimental/AnimateState.h"

Bookmark::Bookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& animateName)
	: BaseActor(
		world,
		modelName,
		position,
		Matrix::Rotation(Vector3::Up(),
		Math::HALF_PI),
		std::make_unique<Sphere>(Vector3::Zero(), 3.0f))
	, m_once(false)
	, m_animateName(animateName)
{
	
}

void Bookmark::onMessage(const std::string& message, void* parameter)
{
	if (!m_once && message == "OnGimmick")
	{
		AnimateState state { m_animateName, false };
		m_world->findGroup(ActorTag::Field)
			->sendMessage("Animate", &state);
		GimmickManager::add(1);
		m_once = true;
	}

	BaseActor::onMessage(message, parameter);
}
