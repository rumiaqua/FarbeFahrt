//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�ӔC��:�Ȃ肽��
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
#pragma once
#include "DxLib.h"

class ISceneMediator;
class SceneManager;
class Loader;
class Renderer;

class BaseScene
{
public:
	friend SceneManager;
public:
	BaseScene();
	virtual void loadContents(Loader& loader) = 0;
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void draw(Renderer& renderer) = 0;
	virtual void post() = 0;
	virtual void cleanUp() = 0;
	virtual bool isSwallow() const = 0;
	virtual ~BaseScene();
private:
	void setManagerPtr(ISceneMediator* const mediator);
protected:
	ISceneMediator* m_manager;
};
