# pragma once

# include <memory>
# include <unordered_map>
# include <functional>

# include "Frame/BaseScene.h"
# include "Utility/Loader.h"
# include "ISceneMediator.h"

// シーン管理
class BaseScene;
using ScenePtr = std::unique_ptr<BaseScene>;
using Scenes = std::unordered_map<Scene, ScenePtr>;
using Stack = std::list<Scene>;

// スタック操作
class Loader;
using Operation = std::function<void(Loader&)>;
using Operations = std::list<Operation>;

class Renderer;

class SceneManager : public ISceneMediator
{
public:

	/// <summary>コンストラクタ</summary>
	SceneManager();

public:

	/// <summary>シーンの追加</summary>
	template <typename Type, typename ...Args>
	void addScene(const Scene & scene, Args && ...args)
	{
		m_scenes.insert(std::make_pair(scene, std::make_unique<Type>(std::forward<Args>(args)...)));
		m_scenes.at(scene)->setManagerPtr(this);
	}

	/// <summary>更新</summary>
	void update();

	/// <summary>描画</summary>
	void draw(Renderer& renderer) const;

	/// <summary>オペレーションを解決する</summary>
	void resolve(Loader& loader);

	/// <summary>シーンの変更があったかどうか</summary>
	bool hasChanged() const;

public:

	/// <summary>基底シーンを変更する</summary>
	virtual void changeScene(const Scene& scene) override;

	/// <summary>トップシーンを変更する</summary>
	virtual void replaceScene(const Scene& scene) override;

	/// <summary>新たなシーンをプッシュする</summary>
	virtual void pushScene(const Scene& scene) override;

	/// <summary>トップシーンをポップする</summary>
	virtual void popScene() override;

private:

	/// <summary>操作を挿入する</summary>
	void pushOperation(const Operation& operation);

private:

	Scenes m_scenes;

	Stack m_stack;

	Operations m_ops;
};
