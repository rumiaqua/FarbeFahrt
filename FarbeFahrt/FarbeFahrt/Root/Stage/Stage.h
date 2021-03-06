# pragma once

# include "Actor/ActorManager/ActorManager.h"
# include "StageData.h"

#include "Scene\SceneManager.h"

class World;

class Stage
{
public:

	Stage(World* world,ISceneMediator* manager);

public:

	/// <summary>ステージデータから構成する</summary>
	/// <param name="data">構成データ</param>
	/// <param name="isClear">アクターリストをクリアするかどうか</param>
	void apply(const StageData& data, bool isClear = true);

	/// <summary>更新</summary>
	void update();

	/// <summary>描画</summary>
	void draw(Renderer& renderer) const;

	/// <summary>アクターの追加</summary>
	/// <param name="tag">アクタータグ</param>
	/// <param name="actor">アクター</param>
	void addActor(const ActorTag& tag, const Actor& actor);

	/// <summary>アクターの検索</summary>
	/// <param name="name">名前</param>
	Actor findActor(const std::string& name) const;

	/// <summary>アクターの検索</summary>
	/// <param name="name">名前</param>
	std::vector<Actor> findActors(const std::string& name) const;

	/// <summary>グループを返す</summary>
	Actor findGroup(const ActorTag& tag) const;

	/// <summary>アクターのクリア</summary>
	void clearActor();

private:

	World* m_world;

	ActorManager m_actorManager;

	std::string m_stageName;
	ISceneMediator* m_manager;
	int m_point;
};
