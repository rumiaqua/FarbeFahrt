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
		//�ӔC�҂Ȃ肽��
		//1.�J����������
		//2.�v���C���[�ɂ͂��΂炭��������ł��炤
		//3.�y�[�W���߂���
		//4.�v���C���[�̈ʒu���Z�b�g
		//5.�J�������߂Â���
		// m_world->findCamera()->sendMessage("nextStage",nullptr);
		bool isKill = true;
		player->sendMessage("StopControl", &isKill);
		kill();
	}
	BaseActor::onMessage(message, parameter);
}
