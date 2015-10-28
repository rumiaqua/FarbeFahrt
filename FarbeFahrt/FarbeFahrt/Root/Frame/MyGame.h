//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//責任者:なりたん
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
#pragma once
#include "DxLib.h"

#include "Utility/Renderer.h"
#include "Utility/Loader.h"

# include "Scene/SceneManager.h"

class MyGame
{
public:
	MyGame();
	void run();
private:
	Renderer render;
	Loader loader;
	bool m_breakflag;
	bool initFlag;
	SceneManager m_sceneManager;
};
