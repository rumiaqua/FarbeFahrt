# pragma once

enum class Scene;

class ISceneMediator
{
protected:

	ISceneMediator() = default;

public:

	/// <summary>基底シーンを変更する</summary>
	virtual void changeScene(const Scene& scene, float t, bool isSwallow = true) = 0;

	/// <summary>トップシーンを変更する</summary>
	virtual void replaceScene(const Scene& scene, float t, bool isSwallow = true) = 0;

	/// <summary>新たなシーンをプッシュする</summary>
	virtual void pushScene(const Scene& scene, float t, bool isSwallow = true) = 0;

	/// <summary>トップシーンをポップする</summary>
	virtual void popScene(float t, bool isSwallow = true) = 0;

public:

	/// <summary>基底シーンを変更する</summary>
	virtual void changeScene(const Scene& scene) = 0;

	/// <summary>トップシーンを変更する</summary>
	virtual void replaceScene(const Scene& scene) = 0;

	/// <summary>新たなシーンをプッシュする</summary>
	virtual void pushScene(const Scene& scene) = 0;

	/// <summary>トップシーンをポップする</summary>
	virtual void popScene() = 0;
};
