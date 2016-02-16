#include "Adele.h"

# include "Utility/Math.h"
# include "Gimmick\GimmickManager.h"
# include "Scene\Scene.h"
Adele::Adele(IWorld& world, const std::string& name, const Vector3& position,ISceneMediator* manager)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3::Zero(), 3.0f))
	,m_isCollide(false)
{
	m_manager = manager;
}

void Adele::onUpdate()
{
	if (m_isCollide)
	{
		m_manager->pushScene(Scene::BlackOut, 60.0f);

		kill();
	}
	BaseActor::onUpdate();
}

void Adele::onDraw(Renderer& renderer) const
{
	if (m_isCollide)
	{

	}
	BaseActor::onDraw(renderer);
}

void Adele::onMessage(const std::string& message, void* parameter)
{

	BaseActor* actor = static_cast<BaseActor*>(parameter);
	if (!isDead() &&
		message == "onCollide" &&
		actor->getName() == "Player")
	{
		m_isCollide = true;
		
		GimmickManager::add(1);
	}
}
