//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�ӔC��:�Ȃ肽��
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
#pragma once
#include "DxLib.h"
#include "Utility/Renderer.h"
#include "Utility/Loader.h"

class ISceneMediator;
class SceneManager;

enum Scene{
	NullScene = 1,
	drawGameTitle,
	drawGameMenu,
	drawGameMain
};
class BaseScene
{
public:
	friend SceneManager;
public:
	BaseScene();
	virtual void loadContents(Loader& loader) = 0;
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void draw(Renderer& render) = 0;
	virtual void cleanUp() = 0;
	virtual ~BaseScene();
private:
	void setManagerPtr(ISceneMediator* const mediator);
protected:
	ISceneMediator* m_manager;
};
