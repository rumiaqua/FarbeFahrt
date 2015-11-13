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
	// フィールドの初期化
	m_field = std::make_shared<Field>(*m_world, data.fieldName, data.fieldScale);

	// プレイヤー位置の初期化
	m_actorManager.addActor(ActorTag::Player, std::make_shared<Player>(
		*m_world, data.playerPosition));

	// その他オブジェクトの初期化
	for (auto&& object : data.objectList)
	{
		// 未実装
		if (object.name == "Gimmick")
		{
			m_world->addActor(ActorTag::Gimmick, std::make_shared<Gimmick>(
				*m_world, object.resource, object.position, 1, 1.0f, 300.0f));
		}
	}
}

void Stage::update()
{
	// 更新処理
	m_field->update();
	m_actorManager.update();

	// フィールドとアクターの衝突処理
	m_actorManager.collideField(m_field.get());
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
