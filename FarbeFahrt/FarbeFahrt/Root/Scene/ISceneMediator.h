# pragma once

enum Scene;

class ISceneMediator
{
protected:

	ISceneMediator() = default;

public:

	/// <summary>���V�[����ύX����</summary>
	virtual void changeScene(const Scene& scene) = 0;

	/// <summary>�g�b�v�V�[����ύX����</summary>
	virtual void replaceScene(const Scene& scene) = 0;

	/// <summary>�V���ȃV�[�����v�b�V������</summary>
	virtual void pushScene(const Scene& scene) = 0;

	/// <summary>�g�b�v�V�[�����|�b�v����</summary>
	virtual void popScene() = 0;
};
