#include "Stage.h"

# include "Actor/Actor.h"
# include "Actor/Field/Field.h"
# include "Actor/ActorManager/ActorManager.h"
# include "Actor/Player.h"
# include "Actor/Gimmick/Gimmick.h"
# include "Actor/Gimmick/TouchGimmick.h"
# include "Actor/Gimmick/CommandGimmick.h"
# include "Actor/SkinObject.h"
# include "Actor/StaticObject.h"
# include "Actor/Goal/Goal.h"
# include "Actor/PlayerSpawner.h"
# include "Actor/Gimmick/GimmickManager.h"
# include "Actor/Instant.h"
# include "Actor/Boat.h"
# include "Actor/ToNight.h"
# include "Actor/MessageObject.h"

# include "World.h"

# include "Manager/MessageManager.h"

# include "Message/MessageOperation.h"

#include "Utility/Debug.h"
#include "Utility/BGM.h"

# include "Experimental/AnimateState.h"
# include "Experimental/Bookmark.h"
# include "Experimental/ActionBookmark.h"
# include "Experimental/CameraBookmark.h"

# include "Actor\Adele.h"

Stage::Stage(World* world,ISceneMediator* manager)
	: m_world(world)
	, m_actorManager()
	, m_point(-1)
{
	m_manager = manager;
}

void Stage::apply(const StageData& data, bool isClear)
{
	// アクターの初期化
	if (isClear)
	{
		clearActor();
	}

	m_stageName = data.filename;

	// フィールドの初期化
	AnimateState state { "Open", false };
	for (auto&& field : data.fieldList)
	{
		auto actor = std::make_shared<Field>(
			*m_world, field.name, field.position, field.scale, field.transition);
		m_actorManager.addActor(ActorTag::Field, actor);
		// actor->sendMessage("OpenAnimate", nullptr);
		actor->sendMessage("Animate", &state);
	}

	// プレイヤー位置の初期化
	{
		m_world->addActor(ActorTag::Player, std::make_shared<PlayerSpawner>(
			*m_world, data.playerPosition, data.noEntries));
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
			float radius = String::ToValue<float>(parameter[3]);
			m_world->addActor(ActorTag::Gimmick, std::make_shared<Gimmick>(
				*m_world, object.resource, object.position, animNo, animSpeed, maxFrame, radius));
		}
		if (object.name == "TouchGimmick")
		{
			auto parameter = String::Split(object.parameter, '/');
			float radius = String::ToValue<float>(parameter[0]);
			m_world->addActor(ActorTag::Gimmick, std::make_shared<TouchGimmick>(
				*m_world, object.resource, object.position, radius));
		}
		if (object.name == "CommandGimmick")
		{
			auto parameter = String::Split(object.parameter, '/');
			int animNo = String::ToValue<int>(parameter[0]);
			float animSpeed = String::ToValue<float>(parameter[1]);
			float maxFrame = String::ToValue<float>(parameter[2]);
			float radius = String::ToValue<float>(parameter[3]);
			int commandNo = String::ToValue<int>(parameter[4]);
			m_world->addActor(ActorTag::Gimmick, std::make_shared<CommandGimmick>(
				*m_world, object.resource, object.position, animNo, animSpeed, maxFrame, radius, commandNo));
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
			float radius = String::ToValue<float>(parameter[6]);
			m_world->addActor(ActorTag::Object, std::make_shared<SkinObject>(
				*m_world, object.resource, object.position, animNo, animSpeed, maxFrame, scale, angle, isLoop, radius));
			// int anmNo, float frameSpeed,float maxframe
		}
		if (object.name == "StaticObject")
		{
			m_world->addActor(ActorTag::Object, std::make_shared<StaticObject>(
				*m_world, object.resource, object.position));
		}
		if (object.name == "Goal")
		{
			auto parameter = String::Split(object.parameter, '/');
			int threshold = parameter[0] != "" ? String::ToValue<int>(parameter[0]) : 0;
			m_world->addActor(ActorTag::Goal, std::make_shared<Goal>(
				*m_world, object.resource, object.position, threshold));
		}		
		if (object.name == "Instant")
		{
			m_world->addActor(ActorTag::Object, std::make_shared<Instant>(
				*m_world, object.resource, object.position, String::Split(object.parameter, '/')));
		}
		//責任者なりたん
		if (object.name == "Adele")
		{
			m_world->addActor(ActorTag::Object, std::make_shared<Adele>(
				*m_world, object.resource, object.position,m_manager));
		}
		//なりたんここまで
		if (object.name == "Bookmark")
		{
			m_world->addActor(ActorTag::Gimmick, std::make_shared<Bookmark>(
				*m_world, object.resource, object.position, object.parameter));
		}
		if (object.name == "Boat")
		{
			m_world->addActor(ActorTag::Gimmick, std::make_shared<Boat>(
				*m_world, object.resource, object.position));
		}
		if (object.name == "ActionBookmark")
		{
			m_world->addActor(ActorTag::Gimmick, std::make_shared<ActionBookmark>(
				*m_world, object.resource, object.position, object.parameter));
		}
		if (object.name == "CameraBookmark")
		{
			auto parameter = String::Split(object.parameter, '/');
			std::string& actionName = parameter[0];
			m_world->addActor(ActorTag::Gimmick, std::make_shared<CameraBookmark>(
				*m_world, object.resource, object.position, actionName));
		}
		if (object.name == "ToNight")
		{
			m_world->addActor(ActorTag::Gimmick, std::make_shared<ToNight>(
				*m_world, object.resource, object.position, m_manager));
		}
		if (object.name == "MessageObject")
		{
			m_world->addActor(ActorTag::Goal, std::make_shared<MessageObject>(
				*m_world, object.resource, object.position, object.parameter));
		}
	}

	m_point = data.gimmickPoint;
	GimmickManager::setMax(data.gimmickPoint);

	// 開始時のメッセージ処理
	if (data.message != "")
	{
		MessageManager::Add(data.message);
	}
}

void Stage::update()
{
	if (GimmickManager::isPoint(m_point))
	{
		StoryManager::set(BitFlag::GIMMICK);
	}
	else
	{
		StoryManager::reset(BitFlag::GIMMICK);
	}

	// 更新処理
	m_actorManager.update();

	// フィールドとアクターの衝突処理
	m_actorManager.collidePlayer(ActorTag::Field);
	m_actorManager.collidePlayer(ActorTag::Gimmick);
	m_actorManager.collidePlayer(ActorTag::Object);
	m_actorManager.findGroup(ActorTag::Field)
		->eachChildren([&](BaseActor& actor) { m_actorManager.findGroup(ActorTag::Object)->collide(&actor); });
}

void Stage::draw(Renderer& renderer) const
{	
	// 描画処理
	m_actorManager.draw(renderer);

	/*Debug::Println("nextPoint:%d", m_point);
	Debug::Println(String::Create("isPoint : ", GimmickManager::isPoint(m_point) ? "true" : "false"));*/

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
