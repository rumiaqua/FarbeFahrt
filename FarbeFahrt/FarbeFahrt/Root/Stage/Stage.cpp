#include "Stage.h"


# include "Actor/Actor.h"
# include "Actor/Field/Field.h"
# include "Actor/ActorManager/ActorManager.h"
# include "Actor/Player.h"
# include "Actor/Gimmick/Gimmick.h"
# include "Actor/SkinObject.h"
# include "Actor/StaticObject.h"
# include "Actor/Goal/Goal.h"
# include "Actor/PlayerSpawner.h"
# include "Actor/Page.h"

# include "World.h"

# include "Manager/MessageManager.h"

#include "Utility/Debug.h"

Stage::Stage(World* world)
	: m_world(world)
	, m_actorManager()
{

}

void Stage::apply(const StageData& data, bool isClear)
{
	// �A�N�^�[�̏�����
	if (isClear)
	{
		clearActor();
	}

	m_stageName = data.filename;

	// �t�B�[���h�̏�����
	for (auto&& field : data.fieldList)
	{
		auto actor = std::make_shared<Field>(
			*m_world, field.name, field.position, field.scale);
		m_actorManager.addActor(ActorTag::Field, actor);
		actor->sendMessage("OpenAnimate", nullptr);
	}

	// �v���C���[�ʒu�̏�����
	{
		m_world->addActor(ActorTag::Player, std::make_shared<PlayerSpawner>(
			*m_world, data.playerPosition));
	}

	// ���̑��I�u�W�F�N�g�̏�����
	for (auto&& object : data.objectList)
	{
		// ������
		if (object.name == "Gimmick")
		{
			auto parameter = String::Split(object.parameter, '/');
			int animNo = String::ToValue<int>(parameter[0]);
			float animSpeed = String::ToValue<float>(parameter[1]);
			float maxFrame = String::ToValue<float>(parameter[2]);
			m_world->addActor(ActorTag::Gimmick, std::make_shared<Gimmick>(
				*m_world, object.resource, object.position, animNo, animSpeed, maxFrame));
		}
		if (object.name == "SkinObject")
		{
			auto parameter = String::Split(object.parameter, '/');
			int animNo = String::ToValue<int>(parameter[0]);
			float animSpeed = String::ToValue<float>(parameter[1]);
			float maxFrame = String::ToValue<float>(parameter[2]);
			float scale = String::ToValue<float>(parameter[3]);
			float angle = String::ToValue<float>(parameter[4]);
			bool isLoop = String::ToValue<int>(parameter[5]) == 1;
			m_world->addActor(ActorTag::Object, std::make_shared<SkinObject>(
				*m_world, object.resource, object.position, animNo, animSpeed, maxFrame, scale, angle, isLoop));
			// int anmNo, float frameSpeed,float maxframe
		}
		if (object.name == "StaticObject")
		{
			m_world->addActor(ActorTag::Object, std::make_shared<StaticObject>(
				*m_world, object.resource, object.position));
		}
		if (object.name == "Goal")
		{
			m_world->addActor(ActorTag::Goal, std::make_shared<Goal>(
				*m_world, object.resource, object.position));
		}
	}

	// �J�n���̃��b�Z�[�W����
	for (auto&& message : data.message)
	{
		MessageManager::Add(message);
	}
}

void Stage::update()
{
	// �X�V����
	m_actorManager.update();

	// �t�B�[���h�ƃA�N�^�[�̏Փˏ���
	m_actorManager.collidePlayer(ActorTag::Field);
	m_actorManager.collidePlayer(ActorTag::Gimmick);
	m_actorManager.collidePlayer(ActorTag::Object);
}

void Stage::draw(Renderer& renderer) const
{	
	// �`�揈��
	m_actorManager.draw(renderer);

	Debug::Println(m_stageName);
}

void Stage::addActor(const ActorTag& tag, const Actor& actor)
{
	m_actorManager.addActor(tag, actor);
}

Actor Stage::findActor(const std::string& name) const
{
	return m_actorManager.findActor(name);
}

std::vector<Actor> Stage::findActors(const std::string & name) const
{
	return m_actorManager.findActors(name);
}

Actor Stage::findGroup(const ActorTag& tag) const
{
	return m_actorManager.findGroup(tag);
}

void Stage::clearActor()
{
	m_actorManager.initialize();
}
