#include "TouchGimmick.h"
#include "Utility/Math.h"
#include "Utility/Input.h"

#include "Utility/Debug.h"
#include "Utility/SingletonFinalizer.h"
#include "Utility/HandleList.h"
#include "Utility/StoryManager/StoryManager.h"

TouchGimmick::TouchGimmick(IWorld & world, const std::string& modelName, const Vector3 & position,float radius) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI / 2), std::make_unique<Sphere>(Vector3::Zero(), radius))
{
	m_name = modelName;
}
void TouchGimmick::onUpdate()
{
	BaseActor::onUpdate();
}

void TouchGimmick::onMessage(const std::string& message, void* parameter)
{
	auto player = m_world->findActor("Player");
	auto gimmickObj = m_world->findActor(m_name.substr(0, m_name.length() - 1));
	auto camera = m_world->findCamera();
	if (player == nullptr) return;
	if (camera == nullptr) return;

	if (message == "onCollide")
	{
		BaseActor* actor = static_cast<BaseActor*>(parameter);
		m_world->actorSet(gimmickObj->getName());
		if (!m_flag)
		{
			m_flag = true;
		}
		else
		{
			m_flag = false;
		}
		actor->sendMessage("HitObstacle", (void*)this);
	}

	BaseActor::onMessage(message, parameter);
}