#pragma once
#include <string>
#include <unordered_map>
#include "Vector3.h"
#include "../../DxLib/DxLib.h"
// 変数を使用しないことを明示する
# define NoUse(Variable) ((void)Variable)

//解像度を取得する
#define nScreenSizeX GetSystemMetrics(SM_CXSCREEN)
#define nScreenSizeY GetSystemMetrics(SM_CYSCREEN)

//画面の中心(ウィンドウの中心じゃないよ)
#define nScreenCenterX (nScreenSizeX / 2)
#define nScreenCenterY (nScreenSizeY / 2)
//Playerクラス
#define ANIM_BLEND_SPEED 0.1f
//Playerクラスここまで

//BGMクラス
#define BGM_MAX_VOLUME 128
//BGMクラスここまで
struct ContentData {
	int handle;
	std::string filename;
	bool use;
	ContentData(int handle, const std::string& filename)
	{
		this->handle = handle;
		this->filename = filename;
		this->use = true;
	}
	ContentData() {}
};
using ContentMap = std::unordered_map<std::string, ContentData>;

const Vector3 LIGHT_POSITION = { 20.0f,100.0f,-70.0f };
const Vector3 LIGHT_TARGET = { -50.0f,-30.0f,-20.0f };

namespace System
{
	RECT GetWindowRect();
	int GetWindowWidth();
	int GetWindowHeight();
};