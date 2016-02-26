# include "Bookmark.h"

# include "Manager/MessageManager.h"

# include "Actor/Gimmick/GimmickManager.h"

# include "Collision/Empty.h"

# include "Utility/Math.h"
# include "Utility/Renderer.h"

# include "Experimental/AnimateState.h"

Bookmark::Bookmark(IWorld& world, const std::string& modelName, const Vector3& position, const std::string& parameter)
	: BaseActor(
		world,
		modelName,
		position,
		Matrix::Rotation(Vector3::Up(),
		Math::HALF_PI),
		std::make_unique<Sphere>(Vector3::Zero(), 15.0f))
	, m_addPoint(1)
	, m_isAddPoint(false)
	, m_isToggle(false)
	, m_animateName()
	, m_access()
	, m_isActive(true)
{
	for (auto&& param : String::Split(parameter, '/'))
	{
		if (param.find("Name") != std::string::npos)
		{
			m_animateName = String::Split(param, ':')[1];
		}
		if (param == "Toggle")
		{
			m_isToggle = true;
		}
		if (param == "AddPoint")
		{
			m_isAddPoint = true;
		}
		if (param.find("Access") != std::string::npos)
		{
			auto split = String::Split(param, ':');
			m_access.x = String::ToValue<float>(split[1]);
			m_access.y = String::ToValue<float>(split[2]);
			m_access.z = String::ToValue<float>(split[3]);
		}
		if (param == "NonActivate")
		{
			m_isActive = false;
		}
	}
}

void Bookmark::onDraw(Renderer& renderer) const
{
	if (m_isActive)
	{
		renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	}
	return BaseActor::onDraw(renderer);
}

void Bookmark::onMessage(const std::string& message, void* parameter)
{
	if (message == "Activate")
	{
		m_isActive = true;
	}

	if (message == "OnGimmick" && m_isActive)
	{
		m_world->actorSet(m_access);

		if (m_isAddPoint)
		{
			GimmickManager::add(m_addPoint);

			if (m_isToggle)
			{
				m_addPoint *= -1;
			}
		}
		if (!m_isToggle)
		{
			m_isAddPoint = false;
			m_shape = std::make_unique<Empty>();
		}

		AnimateState state { m_animateName, false };
		m_world->findGroup(ActorTag::Field)
			->sendMessage("Animate", &state);
	}

	BaseActor::onMessage(message, parameter);
}
