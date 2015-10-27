# pragma once

# include <memory>
# include <unordered_map>
# include <functional>

# include "Frame/BaseScene.h"
# include "Utility/Loader.h"
# include "ISceneMediator.h"

// �V�[���Ǘ�
class BaseScene;
using ScenePtr = std::unique_ptr<BaseScene>;
using Scenes = std::unordered_map<Scene, ScenePtr>;
using Stack = std::list<Scene>;

// �X�^�b�N����
class Loader;
using Operation = std::function<void(Loader&)>;
using Operations = std::list<Operation>;

class Renderer;

class SceneManager : public ISceneMediator
{
public:

	/// <summary>�R���X�g���N�^</summary>
	SceneManager();

public:

	/// <summary>�V�[���̒ǉ�</summary>
	template <typename Type, typename ...Args>
	void addScene(const Scene & scene, Args && ...args)
	{
		m_scenes.insert(std::make_pair(scene, std::make_unique<Type>(std::forward<Args>(args)...)));
		m_scenes.at(scene)->setManagerPtr(this);
	}

	/// <summary>�X�V</summary>
	void update();

	/// <summary>�`��</summary>
	void draw(Renderer& renderer) const;

	/// <summary>�I�y���[�V��������������</summary>
	void resolve(Loader& loader);

	/// <summary>�V�[���̕ύX�����������ǂ���</summary>
	bool hasChanged() const;

public:

	/// <summary>���V�[����ύX����</summary>
	virtual void changeScene(const Scene& scene) override;

	/// <summary>�g�b�v�V�[����ύX����</summary>
	virtual void replaceScene(const Scene& scene) override;

	/// <summary>�V���ȃV�[�����v�b�V������</summary>
	virtual void pushScene(const Scene& scene) override;

	/// <summary>�g�b�v�V�[�����|�b�v����</summary>
	virtual void popScene() override;

private:

	/// <summary>�����}������</summary>
	void pushOperation(const Operation& operation);

private:

	Scenes m_scenes;

	Stack m_stack;

	Operations m_ops;
};
