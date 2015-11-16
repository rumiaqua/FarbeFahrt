#pragma once
#include <string>
#include <unordered_map>

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
struct ContentData{
	int handle;
	std::string filename;
	ContentData(int handle,const std::string& filename)
	{
		this->handle = handle;
		this->filename = filename;
	}
	ContentData(){}
};
using ContentMap = std::unordered_map<std::string, ContentData>;
