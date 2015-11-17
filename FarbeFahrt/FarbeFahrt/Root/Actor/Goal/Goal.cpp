#include "Goal.h"
#include "Utility/Math.h"

#include "Utility/Debug.h"

Goal::Goal(IWorld& world, const String & modelName, const Vector3 & position) :
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
		m_world->findCamera()->sendMessage("complete", nullptr);
		m_world->findCamera()->sendMessage("toBookCamera", nullptr);
		//�ӔC�҂Ȃ肽��
		//1.�J����������
		//2.�v���C���[�ɂ͂��΂炭��������ł��炤
		//3.�y�[�W���߂���
		//4.�v���C���[�̈ʒu���Z�b�g
		//5.�J�������߂Â���
		// m_world->findCamera()->sendMessage("nextStage",nullptr);
		player->sendMessage("StopControl", nullptr);
		kill();
	}
	BaseActor::onMessage(message, parameter);
}
