#pragma once
#include "Scene/SceneManager.h"

enum BitFlag
{
	// フラグが立っていない
	NONE		= 0b0000,
	// ギミックが動作している
	GIMMICK		= 0b0001,
	// ゴールした
	GOAL		= 0b0010,
	// 次のステージに遷移した
	NEXT        = 0b0100,
};

class StoryManager
{
public:
	StoryManager();
	static void initialize();
	static bool get(int flag);
	static void set(int flag);
	static void reset(int flag);
private:
	int m_flag;
};