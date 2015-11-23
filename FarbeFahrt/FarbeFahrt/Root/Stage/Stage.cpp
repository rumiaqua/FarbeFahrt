#include "Stage.h"


# include "Actor/Actor.h"
# include "Actor/SkyDome/Skydome.h"
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

#include "Utility/Debug.h"

Stage::Stage(World* world)
	: m_world(world)
	, m_actorManager()
{

}

void Stage::apply(const StageData& data, bool isClear)
{
	// アクターの初期化
	if (isClear)
	{
		clearActor();
	}

	// フィールドの初期化
	for (auto&& field : data.fieldList)
	{
		m_actorManager.addActor(ActorTag::Field, std::make_shared<Field>(
			*m_world, field.name, field.position, field.scale));
	}

	// プレイヤー位置の初期化
	// もしプレイヤーが存在するならば座標だけ変更する
	if (auto player = m_actorManager.findActor("Player"))
	{
		player->getPosition() = data.playerPosition;
	}
	else
	{
		m_world->addActor(ActorTag::Player, std::make_shared<PlayerSpawner>(
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
		if (object.name == "Page")
		{
			auto parameter = String::Split(object.parameter, '/');
			String backgroundName = parameter[0];
			String groundName = parameter[1];
			bool isOpen = String::ToValue<int>(parameter[2]) == 1;
			float scale = String::ToValue<float>(parameter[3]);
			float angle = String::ToValue<float>(parameter[4]);
			m_world->addActor(ActorTag::Object, std::make_shared<Page>(
				*m_world, object.name, object.position, backgroundName, groundName, isOpen, scale, angle));
			/*m_world->addActor(ActorTag::Object, std::make_shared<SkinObject>(
				*m_world, backgroundName, object.position, 0, 0.1f, 589.0f));
			m_world->addActor(ActorTag::Object, std::make_shared<SkinObject>(
				*m_world, groundName, object.position, 0, 0.1f, 589.0f));*/
		}
	}
}

void Stage::update()
{
	// 更新処理
	m_actorManager.update();

	// フィールドとアクターの衝突処理
	m_actorManager.collideField();
}

void Stage::draw(Renderer& renderer) const
{
	// 描画処理
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

Actor Stage::findGroup(const ActorTag& tag) const
{
	return m_actorManager.findGroup(tag);
}

void Stage::clearActor()
{
	m_actorManager.initialize();
}
