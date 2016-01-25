# include "Bookmark.h"

# include "Actor/Gimmick/GimmickManager.h"

# include "Collision/Empty.h"

# include "Utility/Math.h"
# include "Utility/Renderer.h"

# include "Experimental/AnimateState.h"

Bookmark::Bookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& animateName, bool isAddPoint)
	: BaseActor(
		world,
		modelName,
		position,
		Matrix::Rotation(Vector3::Up(),
		Math::HALF_PI),
		std::make_unique<Sphere>(Vector3::Zero(), 15.0f))
	, m_isAddPoint(isAddPoint)
	, m_animateName(animateName)
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
		if (m_isAddPoint)
		{
			GimmickManager::add(1);
			m_isAddPoint = false;
		}
		AnimateState state { m_animateName, false };
		m_world->findGroup(ActorTag::Field)
			->sendMessage("Animate", &state);
		m_shape = std::make_unique<Empty>();
	}

	BaseActor::onMessage(message, parameter);
}
