#include "Stage.h"


# include "Actor/Actor.h"
# include "Actor/SkyDome/Skydome.h"
# include "Actor/Field/Field.h"
# include "Actor/ActorManager/ActorManager.h"
# include "Actor/Player.h"
# include "Actor/Gimmick/Gimmick.h"
# include "Actor/SkinObject.h"

# include "World.h"

#include "Utility/Debug.h"

# include "Actor/Goal/Goal.h"

Stage::Stage(World* world)
	: m_world(world)
	, m_field()
	, m_actorManager()
{

}

void Stage::apply(const StageData& data, bool isClear)
{
	// フィールドの初期化
	m_field = std::make_shared<Field>(*m_world, data.fieldName, data.fieldScale);

	// アクターの初期化
	if (isClear)
	{
		clearActor();
	}

	// プレイヤー位置の初期化
	// もしプレイヤーが存在するならば座標だけ変更する
	if (auto player = m_actorManager.findActor("Player"))
	{
		player->getPosition() = data.playerPosition;
	}
	else
	{
		m_world->addActor(ActorTag::Player, std::make_shared<Player>(
			*m_world, data.playerPosition));
	}

	// その他オブジェクトの初期化
	for (auto&& object : data.objectList)
	{
		// 未実装
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
			m_world->addActor(ActorTag::Object, std::make_shared<SkinObject>(
				*m_world, object.resource, object.position, animNo, animSpeed, maxFrame));
			// int anmNo, float flameSpeed,float maxFlame
		}
	}

	m_world->addActor(ActorTag::Goal, std::make_shared<Goal>(
		*m_world, "test", Vector3(100, -80, -30)));
}

void Stage::update()
{
	// 更新処理
	m_field->update();
	m_actorManager.update();

	// フィールドとアクターの衝突処理
	m_actorManager.collideField(m_field.get());

	Debug::Println("%d",m_world->getFlag());
}

void Stage::draw(Renderer& renderer) const
{
	// 描画処理
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

void Stage::clearActor()
{
	m_actorManager.initialize();
}
