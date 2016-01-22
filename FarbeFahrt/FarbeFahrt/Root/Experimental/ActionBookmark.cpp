# include "ActionBookmark.h"

ActionBookmark::ActionBookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& targetName, const std::string& actionName)
	: BaseActor(world, modelName, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 15.0f))
	, m_targetName(targetName)
	, m_actionName(actionName)
	, m_once(false)
{

}

void ActionBookmark::onMessage(const std::string& message, void* parameter)
{
	if (message == "OnGimmick")
	{
		if (!m_once)
		{
			m_once = true;
			m_world->findActor(m_targetName)->sendMessage(m_actionName, nullptr);
		}
	}

	BaseActor::onMessage(message, parameter);
}
