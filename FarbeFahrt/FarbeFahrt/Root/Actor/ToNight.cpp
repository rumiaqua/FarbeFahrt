# include "ToNight.h"

# include "Utility/Math.h"

# include "Scene/ISceneMediator.h"
# include "Scene/Scene.h"

ToNight::ToNight(IWorld& world, const std::string& name, const Vector3& position, ISceneMediator* mediator)
	: BaseActor(
		world,
		name,
		position,
		Matrix::Rotation(Vector3::Up(), Math::HALF_PI),
		std::make_unique<Sphere>(Vector3::Zero(), 15.0f))
	, m_mediator(mediator)
{

}

void ToNight::onMessage(const std::string& message, void* parameter)
{
	if (message == "OnGimmick" && !m_dead)
	{
		m_mediator->pushScene(Scene::BlackOut, 60.0f);
		kill();
	}

	BaseActor::onMessage(message, parameter);
}
