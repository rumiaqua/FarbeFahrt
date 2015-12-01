#include "_Camera.h"

_Camera::_Camera(IWorld& world)
	: BaseActor(world, "", Vector3::Zero(), Matrix::identity(), nullptr)
{

}

void _Camera::actorSet(const std::string& name)
{

}

void _Camera::onUpdate()
{

}

void _Camera::onDraw(Renderer& renderer) const
{

}

void _Camera::onMessage(const std::string& message, void* parameter)
{

}
