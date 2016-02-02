# include "Bookmark.h"

# include "Actor/Gimmick/GimmickManager.h"

# include "Utility/Math.h"
# include "Utility/Renderer.h"

# include "Experimental/AnimateState.h"

Bookmark::Bookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& animateName, bool once, const Vector3& access)
	: BaseActor(
		world,
		modelName,
		position,
		Matrix::Rotation(Vector3::Up(),
		Math::HALF_PI),
		std::make_unique<Sphere>(Vector3::Zero(), 15.0f))
	, m_once(once)
	, m_animateName(animateName)
	, m_access(access)
{
	
}

void Bookmark::onDraw(Renderer& renderer) const
{
	renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	return BaseActor::onDraw(renderer);
}

void Bookmark::onMessage(const std::string& message, void* parameter)
{
	if (message == "OnGimmick")
	{
		m_world->actorSet(m_access);
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
