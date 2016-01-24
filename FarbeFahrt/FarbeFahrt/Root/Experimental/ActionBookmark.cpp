# include "ActionBookmark.h"
# include "Utility/Renderer.h"
# include "Utility/Math.h"

# include "Collision/Empty.h"

ActionBookmark::ActionBookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& targetName, const std::string& actionName)
	: BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(),
		Math::HALF_PI), std::make_shared<Sphere>(Vector3::Zero(), 15.0f))
	, m_targetName(targetName)
	, m_actionName(actionName)
	, m_once(false)
{

}

void ActionBookmark::onDraw(Renderer & renderer) const
{
	renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	BaseActor::onDraw(renderer);
}

void ActionBookmark::onMessage(const std::string& message, void* parameter)
{
	if (message == "OnGimmick")
	{
		if (!m_once)
		{
			m_once = true;
			m_world->findActor(m_targetName)->sendMessage(m_actionName, nullptr);
			m_shape = std::make_unique<Empty>();
		}
	}

	BaseActor::onMessage(message, parameter);
}
