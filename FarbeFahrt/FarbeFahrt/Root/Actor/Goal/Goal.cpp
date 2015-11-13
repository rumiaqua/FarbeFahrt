#include "Goal.h"
#include "Utility/Math.h"

#include "Utility/Debug.h"

Goal::Goal(IWorld & world, const String & modelName, const Vector3 & position) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Sphere>(Vector3::Zero(), 10.0f))
	, m_capsule(position, position, 5.0f)
{
	m_name = modelName;
}

void Goal::onDraw(Renderer & render) const
{
	render.drawNormalModel(m_name.toNarrow(), getPosition(), getRotation());

	BaseActor::onDraw(render);
}

void Goal::onMessage(const String & message, void* parameter)
{
	auto player = static_cast<BaseActor*>(parameter);
	if (message == "onCollide" && player->getName() == "Player")
	{
		player->sendMessage("Goal",nullptr);
	}
	BaseActor::onMessage(message, parameter);
}
