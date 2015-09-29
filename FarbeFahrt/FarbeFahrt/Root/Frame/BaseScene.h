//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�ӔC��:�Ȃ肽��
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
#pragma once
#include "DxLib.h"
#include "Utility/Renderer.h"
#include "Utility/Loader.h"
enum Scene{
	NullScene = 1,
	drawGameTitle,
	drawGameMenu,
	drawGameMain
};
class BaseScene
{
public:
	BaseScene();
	virtual void loadContents(Loader& loader) = 0;
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void draw(Renderer& render) = 0;
	virtual void cleanUp() = 0;
	//refreshScene��MyGame�ŌĂяo���p�������
	//�V�[����ς���Ƃ���changeScene�������
	void refreshScene(Scene *scene);
	bool isChangeScene(Scene scene);
	bool isCleanUp();
	virtual ~BaseScene();
protected:
	void changeScene(Scene scene);
protected:
};
