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
	// �f�B���C���Ԃ��߂��Ă����
	if (m_isActive && (m_delay -= 1.0f) < 0.0f)
	{
		// �ړ�
		m_pose.position += Vector3::Right();
	}

	// �v���C���[���Z�b�g����Ă����
	if (!m_player.expired())
	{
		// ���W�̃Z�b�g
		Vector3 position = getPosition() + m_relative;
		m_player.lock()->sendMessage("SetPosition", &position);
	}

	// �ړ�����
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

		// �v���C���[�������Ȃ�
		if (m_player.expired())
		{
			// �v���C���[�����݂����
			if (auto player = m_world->findActor("Player"))
			{
				// �v���C���[�ƏՓ˂��Ă����
				if (this->isCollide(player.get()))
				{
					GimmickManager::add(1);

					// ����𖳌��ɂ���
					bool isKill = false;
					player->sendMessage("StopControl", &isKill);
					player->sendMessage("RefreshNoEntry", nullptr);

					// �v���C���[�̃Z�b�g
					m_player = player;

					// ���΍��W�̃Z�b�g
					m_relative = player->getPosition() - getPosition();
				}
			}
		}
	}

	return BaseActor::onMessage(message, parameter);
}
