# include "Boat.h"
# include "Gimmick\GimmickManager.h"
# include "Utility/Renderer.h"

Boat::Boat(IWorld& world, const std::string& name, const Vector3& position)
	: BaseActor(world, name, position, Matrix::identity(), std::make_shared<Sphere>(Vector3(0.0f, 0.0f, -25.0f), 10.0f))
	, m_isActive(false)
	, m_player()
	, m_delay(300.0f)
{

}

void Boat::onUpdate()
{
	// ディレイ時間を過ぎていれば
	if (m_isActive && (m_delay -= 1.0f) < 0.0f)
	{
		// 移動
		m_pose.position += Vector3::Right();
	}

	// プレイヤーがセットされていれば
	if (!m_player.expired())
	{
		// 座標のセット
		Vector3 position = getPosition() + m_relative;
		m_player.lock()->sendMessage("SetPosition", &position);
	}

	// 移動制限
	const float Limit = 142.0f - (145.0f / 2.0f - 4.0f);
	if (m_pose.position.x > Limit)
	{
		m_pose.position.x = Limit;
		m_world->findCamera()->sendMessage("resetPoint",nullptr);
	}

	BaseActor::onUpdate();
}

void Boat::onDraw(Renderer& renderer) const
{
	renderer.setScale(m_name, { 4.0f, 4.0f, 4.0f });
	renderer.drawNormalModel(m_name, m_pose.position, m_pose.rotation);
	BaseActor::onDraw(renderer);
}

void Boat::onMessage(const std::string& message, void* parameter)
{
	BaseActor* actor = static_cast<BaseActor*>(parameter);
	if (message == "Activate")
	{
		m_isActive = true;

		// プレイヤーが無効なら
		if (m_player.expired())
		{
			// プレイヤーが存在すれば
			if (auto player = m_world->findActor("Player"))
			{
				// プレイヤーと衝突していれば
				if (this->isCollide(player.get()))
				{
					GimmickManager::add(1);

					// 操作を無効にする
					bool isKill = false;
					player->sendMessage("StopControl", &isKill);
					player->sendMessage("RefreshNoEntry", nullptr);

					// プレイヤーのセット
					m_player = player;

					// 相対座標のセット
					m_relative = player->getPosition() - getPosition();
				}
			}
		}
	}

	return BaseActor::onMessage(message, parameter);
}
