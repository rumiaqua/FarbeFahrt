# include "ActionBookmark.h"
# include "Utility/Renderer.h"
# include "Utility/Math.h"

# include "Collision/Empty.h"

ActionBookmark::ActionBookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& parameter)
	: BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(),
		Math::HALF_PI), std::make_shared<Sphere>(Vector3::Zero(), 15.0f))
	, m_targetName()
	, m_actionName()
	, m_once(false)
	, m_isActive(true)
{
	for (auto&& param : String::Split(parameter, '/'))
	{
		if (param == "NonActivate")
		{
			m_isActive = false;
		}
		if (param.find("Name") != std::string::npos)
		{
			m_targetName = String::Split(param, ':')[1];
		}
		if (param.find("Message") != std::string::npos)
		{
			m_actionName = String::Split(param, ':')[1];
		}
	}
}

void ActionBookmark::onDraw(Renderer& renderer) const
{
	BaseActor::onDraw(renderer);
}

void ActionBookmark::onMessage(const std::string& message, void* parameter)
{
	if (message == "OnGimmick")
	{
		if (m_isActive && !m_once)
		{
			m_once = true;
			m_world->findActor(m_targetName)->sendMessage(m_actionName, nullptr);
			m_shape = std::make_unique<Empty>();
		}
	}

	if (message == "Activate")
	{
		m_isActive = true;
	}

	BaseActor::onMessage(message, parameter);
}
