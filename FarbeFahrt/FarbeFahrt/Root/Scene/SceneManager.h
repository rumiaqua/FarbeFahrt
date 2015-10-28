# pragma once

# include <memory>
# include <unordered_map>
# include <functional>

# include "Frame/BaseScene.h"

# include "ISceneMediator.h"

namespace
{
	// �V�[���Ǘ�
	using ScenePtr = std::shared_ptr<BaseScene>;
	using Scenes = std::unordered_map<Scene, ScenePtr>;
	using Stack = std::list<ScenePtr>;

	// �X�^�b�N����
	using Operation = std::function<void(Loader&)>;
	using Operations = std::list<Operation>;
}

class SceneManager : public ISceneMediator
{
private:

	/// <summary>�t�F�[�h�C����p�V�[��</summary>
	class FadeIn final : public BaseScene
	{
	public:

		FadeIn(float fadeCount, bool isSwallow = false);

		void loadContents(Loader& loader) override;

		void initialize() override;

		void update() override;

		void draw(Renderer& renderer) override;

		void cleanUp() override;

		bool isSwallow() const override;

	private:

		const float m_fadeCount;

		float m_currentCount;

		const bool m_isSwallow;
	};

	/// <summary>�t�F�[�h�A�E�g��p�V�[��</summary>
	class FadeOut final : public BaseScene
	{
	public:

		FadeOut(float fadeCount, const std::function<void()>& operation, bool isSwallow = false);

		void loadContents(Loader& loader) override;

		void initialize() override;

		void update() override;

		void draw(Renderer& renderer) override;

		void cleanUp() override;

		bool isSwallow() const override;

	private:

		const float m_fadeCount;

		float m_currentCount;

		const std::function<void()> m_operation;

		const bool m_isSwallow;
	};

public:

	/// <summary>�R���X�g���N�^</summary>
	SceneManager();

public:

	/// <summary>�V�[���̒ǉ�</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	/// <param name="args">�R���X�g���N�^����</param>
	template <typename Type, typename ...Args>
	void addScene(const Scene& scene, Args&& ...args)
	{
		m_scenes.insert(std::make_pair(scene, std::make_shared<Type>(std::forward<Args>(args)...)));
		m_scenes.at(scene)->setManagerPtr(this);
	}

	/// <summary>�X�V</summary>
	void update();

	/// <summary>�`��</summary>
	/// <param name="renderer">Renderer�I�u�W�F�N�g</param>
	void draw(Renderer& renderer) const;

	/// <summary>�I�y���[�V��������������</summary>
	/// <param name="loader">Loader�I�u�W�F�N�g</param>
	void resolve(Loader& loader);

	/// <summary>�V�[���̕ύX�����������ǂ���</summary>
	bool hasChanged() const;

public:

	/// <summary>���V�[����ύX����</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	/// <param name="t">�t�F�[�h�ɂ�����t���[����</param>
	virtual void changeScene(const Scene& scene, float t, bool isSwallow) override;

	/// <summary>�g�b�v�V�[����ύX����</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	/// <param name="t">�t�F�[�h�ɂ�����t���[����</param>
	virtual void replaceScene(const Scene& scene, float t, bool isSwallow) override;

	/// <summary>�V���ȃV�[�����v�b�V������</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	/// <param name="t">�t�F�[�h�ɂ�����t���[����</param>
	virtual void pushScene(const Scene& scene, float t, bool isSwallow) override;

	/// <summary>�g�b�v�V�[�����|�b�v����</summary>
	/// <param name="t">�t�F�[�h�ɂ�����t���[����</param>
	virtual void popScene(float t, bool isSwallow) override;

public:

	/// <summary>���V�[����ύX����</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	virtual void changeScene(const Scene& scene) override;

	/// <summary>�g�b�v�V�[����ύX����</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	virtual void replaceScene(const Scene& scene) override;

	/// <summary>�V���ȃV�[�����v�b�V������</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	virtual void pushScene(const Scene& scene) override;

	/// <summary>�g�b�v�V�[�����|�b�v����</summary>
	/// <param name="scene">�V�[�����ʎq</param>
	virtual void popScene() override;

private:

	/// <summary>�V�[�����X�^�b�N�ɒǉ�</summary>
	void push(const ScenePtr& scene, Loader& loader);

	/// <summary>�擪�̃V�[�����X�^�b�N����폜</summary>
	void pop();

	/// <summary>�S�ẴV�[�����X�^�b�N����폜</summary>
	void clear();

	/// <summary>�����}������</summary>
	void pushOperation(const Operation& operation);

private:

	Scenes m_scenes;

	Stack m_stack;

	Operations m_ops;
};
