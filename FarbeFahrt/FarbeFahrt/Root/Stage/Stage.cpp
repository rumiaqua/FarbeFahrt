#include "Stage.h"


# include "Actor/Actor.h"
# include "Actor/SkyDome/Skydome.h"
# include "Actor/Field/Field.h"
# include "Actor/ActorManager/ActorManager.h"
# include "Actor/Player.h"
# include "Actor/Gimmick/Gimmick.h"

# include "World.h"

Stage::Stage(World* world)
	: m_world(world)
	, m_field()
	, m_actorManager()
{

}

void Stage::apply(const StageData& data)
{
	// �t�B�[���h�̏�����
	m_field = std::make_shared<Field>(*m_world, data.fieldName, data.fieldScale);

	// �v���C���[�ʒu�̏�����
	m_actorManager.addActor(ActorTag::Player, std::make_shared<Player>(
		*m_world, data.playerPosition));

	// ���̑��I�u�W�F�N�g�̏�����
	for (auto&& object : data.objectList)
	{
		// ������
		if (object.name == "Gimmick")
		{
			m_world->addActor(ActorTag::Gimmick, std::make_shared<Gimmick>(
				*m_world, object.resource, object.position, 1, 1.0f, 300.0f));
		}
	}
}

void Stage::update()
{
	// �X�V����
	m_field->update();
	m_actorManager.update();

	// �t�B�[���h�ƃA�N�^�[�̏Փˏ���
	m_actorManager.collideField(m_field.get());
}

void Stage::draw(Renderer& renderer) const
{
	// �`�揈��
	if (m_field)
	{
		m_field->draw(renderer);
	}
	m_actorManager.draw(renderer);
}

void Stage::addActor(const ActorTag& tag, const Actor& actor)
{
	m_actorManager.addActor(tag, actor);
}

Actor Stage::findActor(const std::string& name) const
{
	return m_actorManager.findActor(name);
}

Actor Stage::findField() const
{
	return m_field;
}
