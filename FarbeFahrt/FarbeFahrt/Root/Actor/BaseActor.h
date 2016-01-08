#pragma once
#include "Utility/Renderer.h"
# include "Utility/Pose.h"
# include "Utility/String.h"

#include "IWorld.h"
#include "Actor.h"

#include <string>
#include <algorithm>
#include <functional>
#include <forward_list>

class IShape;
using IShapePtr = std::shared_ptr<IShape>;

/// <summary>アクター基底クラス</summary>
class BaseActor
{
public:

	/// <summary>コンストラクタ</summary>
	BaseActor(IWorld& world, const std::string& name, const Vector3& position, const Matrix& rotation, const IShapePtr& shape);

	explicit BaseActor(const std::string& name = "none");

	/// <summary>仮想デストラクタ</summary>
	virtual ~BaseActor();

	/// <summary>更新</summary>
	void update();

	/// <summary>描画</summary>
	void draw(Renderer& renderer) const;

	/// <summary>衝突判定</summary>
	void collide(BaseActor* folder);

	/// <summary>死亡しているかを返す</summary>
	bool isDead()const;

	/// <summary>殺す</summary>
	void kill();

	/// <summary>名前を取得する</summary>
	const std::string& getName()const;

	/// <summary>姿勢を返す</summary>
	Matrix getPose() const;

	/// <summary>ワールド姿勢を返す</summary>
	Matrix getWorldPose() const;

	/// <summary>座標を返す</summary>
	Vector3& getPosition();

	/// <summary>座標を返す</summary>
	const Vector3& getPosition() const;

	/// <summary>回転を返す</summary>
	Matrix& getRotation();

	/// <summary>回転を返す</summary>
	const Matrix& getRotation() const;

	/// <summary>子を検索</summary>
	Actor find(const std::string& name) const;

	/// <summary>条件に一致する子を検索する</summary>
	Actor findPred(const std::function<bool(const BaseActor&)>& func) const;

	/// <summary>子を検索</summary>
	std::vector<Actor> finds(const std::string& name) const;

	/// <summary>子に追加</summary>
	void addChild(const Actor& child);

	/// <summary>子に処理を実行する</summary>
	void eachChildren(const std::function<void(BaseActor&)>& func);

	/// <summary>子に処理を実行する</summary>
	void eachChildren(const std::function<void(const BaseActor&)>& func)const;

	/// <summary>条件に一致する子を削除する</summary>
	void removeChildren(const std::function<bool(BaseActor&)>& func);

	/// <summary>子を全て削除する</summary>
	void removeChildren();

	/// <summary>メッセージを送信する</summary>
	void sendMessage(const std::string& message, void* parameter);

	/// <summary>コピーコンストラクタを削除</summary>
	BaseActor(const BaseActor& other) = delete;

	/// <summary>代入演算子を削除</summary>
	BaseActor& operator = (const BaseActor& other) = delete;

	bool isCollide(const BaseActor* other) const;

	IShape* const getShape() const;

protected:

	/// <summary>更新</summary>
	virtual void onUpdate();

	/// <summary>描画</summary>
	virtual void onDraw(Renderer& render)const;

	/// <summary>衝突応答</summary>
	virtual void onCollide(BaseActor* actor);
public:
	/// <summary>メッセージを受信</summary>
	virtual void onMessage(const std::string& message, void* parameter);

protected:

	/// <summary>ワールド</summary>
	IWorld* m_world;

	/// <summary>名前</summary>
	std::string m_name;

	/// <summary>姿勢</summary>
	Pose m_pose;

	Pose m_previousPose;

	/// <summary>死亡しているか</summary>
	bool m_dead;

	/// <summary>親アクターポインタ</summary>
	ActorRef m_parent;

	/// <summary>子アクターリスト</summary>
	std::forward_list<Actor> m_children;

	/// <summary>衝突図形</summary>
	IShapePtr m_shape;
};
