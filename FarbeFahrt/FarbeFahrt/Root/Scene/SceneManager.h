# pragma once

# include "ISceneMediator.h"

# include <memory>
# include <unordered_map>
# include <functional>

class BaseScene;
class FadeOut;
class Loader;
class Renderer;

namespace
{
	// シーン管理
	using ScenePtr = std::shared_ptr<BaseScene>;
	using Scenes = std::unordered_map<Scene, ScenePtr>;
	using Stack = std::list<ScenePtr>;

	// スタック操作
	using Operation = std::function<void(Loader&)>;
	using Operations = std::list<Operation>;
}

class SceneManager : public ISceneMediator
{
public:

	friend FadeOut;

public:

	/// <summary>コンストラクタ</summary>
	SceneManager();

public:

	template <typename Type, typename ...Args>
	ScenePtr create(Args&& ...args)
	{
		ScenePtr scene = std::make_shared<Type>(
			std::forward<Args>(args)...);
		scene->m_manager = this;
		return scene;
	}

	/// <summary>シーンの追加</summary>
	/// <param name="scene">シーン識別子</param>
	/// <param name="args">コンストラクタ引数</param>
	template <typename Type, typename ...Args>
	void addScene(const Scene& scene, Args&& ...args)
	{
		m_scenes.insert(std::make_pair(
			scene, create<Type>(std::forward<Args>(args)...)));
	}

	/// <summary>更新</summary>
	void update();

	/// <summary>描画</summary>
	/// <param name="renderer">Rendererオブジェクト</param>
	void draw(Renderer& renderer) const;

	/// <summary>オペレーションを解決する</summary>
	/// <param name="loader">Loaderオブジェクト</param>
	void resolve(Loader& loader);

	/// <summary>事後処理</summary>
	void post();

	/// <summary>シーンの変更があったかどうか</summary>
	bool hasChanged() const;

public:

	/// <summary>基底シーンを変更する</summary>
	/// <param name="scene">シーン識別子</param>
	/// <param name="t">フェードにかかるフレーム数</param>
	virtual void changeScene(const Scene& scene, float t, bool isSwallow) override;

	/// <summary>トップシーンを変更する</summary>
	/// <param name="scene">シーン識別子</param>
	/// <param name="t">フェードにかかるフレーム数</param>
	virtual void replaceScene(const Scene& scene, float t, bool isSwallow) override;

	/// <summary>新たなシーンをプッシュする</summary>
	/// <param name="scene">シーン識別子</param>
	/// <param name="t">フェードにかかるフレーム数</param>
	virtual void pushScene(const Scene& scene, float t, bool isSwallow) override;

	/// <summary>トップシーンをポップする</summary>
	/// <param name="t">フェードにかかるフレーム数</param>
	virtual void popScene(float t, bool isSwallow) override;

public:

	/// <summary>基底シーンを変更する</summary>
	/// <param name="scene">シーン識別子</param>
	virtual void changeScene(const Scene& scene) override;

	/// <summary>トップシーンを変更する</summary>
	/// <param name="scene">シーン識別子</param>
	virtual void replaceScene(const Scene& scene) override;

	/// <summary>新たなシーンをプッシュする</summary>
	/// <param name="scene">シーン識別子</param>
	virtual void pushScene(const Scene& scene) override;

	/// <summary>トップシーンをポップする</summary>
	/// <param name="scene">シーン識別子</param>
	virtual void popScene() override;

private:

	/// <summary>シーンをスタックに追加</summary>
	void push(const ScenePtr& scene, Loader& loader);

	/// <summary>先頭のシーンをスタックから削除</summary>
	void pop();

	/// <summary>全てのシーンをスタックから削除</summary>
	void clear();

	/// <summary>操作を挿入する</summary>
	void pushOperation(const Operation& operation);

private:

	Scenes m_scenes;

	Stack m_stack;

	Operations m_ops;
};
