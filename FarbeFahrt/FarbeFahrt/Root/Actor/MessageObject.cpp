# include "MessageObject.h"

# include "Manager/MessageManager.h"

MessageObject::MessageObject(IWorld& world, const std::string& name, const Vector3 & position, const std::string& message)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 10.0f))
	, m_message(message)
{

}

void MessageObject::onMessage(const std::string& message, void* parameter)
{
	BaseActor* actor = static_cast<BaseActor*>(parameter);
	if (!isDead() &&
		message == "onCollide" &&
		actor->getName() == "Player")
	{
		MessageManager::Add(m_message);
		MessageManager::SetShow(true);
		kill();
	}

	if (message == "Kill")
	{
		kill();
	}

	BaseActor::onMessage(message, parameter);
}
