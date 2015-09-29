//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//責任者:なりたん
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
#pragma once
#include "DxLib.h"
#include <Windows.h>
#include <unordered_map>
#include <functional>
#include "BaseScene.h"
#include <memory>
#include "Utility/Renderer.h"
#include "Utility/Loader.h"
class MyGame
{
public:
	MyGame();
	void run();
private:
	Scene m_scene;
	Renderer render;
	Loader loader;
	bool m_breakflag;
	bool initFlag;
	std::unordered_map<Scene, std::unique_ptr<BaseScene>>func;
};
