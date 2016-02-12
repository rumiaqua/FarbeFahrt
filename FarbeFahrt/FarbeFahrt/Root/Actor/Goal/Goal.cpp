#include "Goal.h"
#include "Utility/Math.h"
#include "Actor/Particle/LightParticleGenerator.h"

#include "Utility/Debug.h"

# include "Actor/Gimmick/GimmickManager.h"
#include "Utility/StoryManager/StoryManager.h"

Goal::Goal(IWorld& world, const std::string& modelName, const Vector3 & position, int threshold) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Sphere>(Vector3::Zero(), 10.0f))
	, m_threthold(threthold)
	, m_particled(false)
{
	m_name = modelName;
}

void Goal::onUpdate()
{
	if (!m_particled)
	{
		m_world->addActor(ActorTag::Effect, std::make_shared<LightParticleGenerator>(*m_world, getPosition(), static_cast<Sphere*>(getShape())->radius));
		m_particled = true;
	}
}

void Goal::onDraw(Renderer & renderer) const
{
	// renderer.drawNormalModel(m_name, getPosition(), getRotation());

	BaseActor::onDraw(renderer);
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
