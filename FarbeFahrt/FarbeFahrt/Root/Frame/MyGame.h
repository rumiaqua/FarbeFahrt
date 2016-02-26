//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//責任者:なりたん
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
#pragma once
#include "DxLib.h"

#include "Utility/Renderer.h"
#include "Utility/Loader.h"

#include "Scene/SceneManager.h"
#include "Utility\NowLoading.h"

class MyGame
{
public:
	MyGame();
	void run();
	bool isEnd() const;

private:
	bool checkNotOperation();

private:
	Renderer renderer;
	Loader loader;
	bool m_breakflag;
	bool initFlag;
	SceneManager m_sceneManager;
	NowLoading m_nowLoading;
	float m_timer;
};
