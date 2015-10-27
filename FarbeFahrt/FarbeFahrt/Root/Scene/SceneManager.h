# pragma once

# include <memory>
# include <unordered_map>
# include <deque>
# include <functional>

class BaseScene;
using ScenePtr = std::unique_ptr<BaseScene>;
enum Scene;
using Scenes = std::unordered_map<Scene, ScenePtr>;
using Stack = std::deque<Scene>;
using Operation = std::function<void()>;
using Operations = std::list<Operation>;

class ISceneMediator
{
protected:

	ISceneMediator() = default;

public:
	virtual void changeScene(const Scene& scene) = 0;

	virtual void replaceScene(const Scene& scene) = 0;

	virtual void pushScene(const Scene& scene) = 0;

	virtual void popScene() = 0;
};

class SceneManager : public ISceneMediator
{
public:

	SceneManager();

public:

	/// <summary>���V�[����ύX����</summary>
	virtual void changeScene(const Scene& scene) override;

	/// <summary>�g�b�v�V�[����ύX����</summary>
	virtual void replaceScene(const Scene& scene) override;

	/// <summary>�V���ȃV�[�����v�b�V������</summary>
	virtual void pushScene(const Scene& scene) override;

	/// <summary>�g�b�v�V�[�����|�b�v����</summary>
	virtual void popScene() override;

public:

	/// <summary>�I�y���[�V��������������</summary>
	void Resolve();
private:

	Scenes m_scenes;

	Stack m_stack;

	Operations m_ops;
};
