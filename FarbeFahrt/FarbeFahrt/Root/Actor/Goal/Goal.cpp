#include "Goal.h"
#include "Utility/Math.h"

#include "Utility/Debug.h"

# include "Actor/Gimmick/GimmickManager.h"

Goal::Goal(IWorld& world, const std::string& modelName, const Vector3 & position, int threshold) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Sphere>(Vector3::Zero(), 10.0f))
	, m_threshold(threshold)
{

	m_name = modelName;
}

void Goal::onDraw(Renderer & render) const
{
	// render.drawNormalModel(m_name, getPosition(), getRotation());

	BaseActor::onDraw(render);
}

void Goal::onMessage(const std::string& message, void* parameter)
{
	auto player = static_cast<BaseActor*>(parameter);

	int gimmick = GimmickManager::get();
	if (gimmick >= m_threshold &&
		message == "onCollide" &&
		player->getName() == "Player")
	{
		m_world->findCamera()->sendMessage("complete", nullptr);
		m_world->findCamera()->sendMessage("toBookCamera", nullptr);
		//責任者なりたん
		//1.カメラを引く
		//2.プレイヤーにはしばらく引っ込んでもらう
		//3.ページをめくる
		//4.プレイヤーの位置をセット
		//5.カメラを近づける
		// m_world->findCamera()->sendMessage("nextStage",nullptr);
		bool isKill = true;
		player->sendMessage("StopControl", &isKill);
		kill();
	}
	BaseActor::onMessage(message, parameter);
}
