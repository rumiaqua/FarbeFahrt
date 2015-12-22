#include "TouchGimmick.h"
#include "Utility/Math.h"
#include "Utility/Input.h"

#include "Utility/Debug.h"
#include "Utility/SingletonFinalizer.h"
#include "Utility/HandleList.h"
#include "Utility/StoryManager/StoryManager.h"
#include "Actor/Gimmick/GimmickManager.h"
#include "Stage/Stage.h"

TouchGimmick::TouchGimmick(IWorld & world, const std::string& modelName, const Vector3 & position,float radius) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI / 2), std::make_unique<Sphere>(Vector3::Zero(), radius))
{
	m_name = modelName;
	m_flag = false;
}
void TouchGimmick::onUpdate()
{
	if (m_flag)
	{
		StoryManager::set(BitFlag::GIMMICK);
	}

	BaseActor::onUpdate();
}

void TouchGimmick::onDraw(Renderer & render) const
{
	render.drawNormalModel(m_name, getPosition(), getRotation());

	BaseActor::onDraw(render);
}

void TouchGimmick::onMessage(const std::string& message, void* parameter)
{
	auto gimmickObj = m_world->findActor(m_name.substr(0, m_name.length() - 1));
	auto camera = m_world->findCamera();
	if (camera == nullptr) return;

	BaseActor* actor = static_cast<BaseActor*>(parameter);
	if (message == "onCollide" && actor->getName() == "Player")
	{
		if (!m_flag && GimmickManager::isPoint(GimmickManager::getMax()))
		{
			m_flag = true;
		}
	}

	BaseActor::onMessage(message, parameter);
}


