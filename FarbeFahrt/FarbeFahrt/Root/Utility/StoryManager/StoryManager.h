#pragma once
#include "Scene/SceneManager.h"

enum BitFlag
{
	NONE		= 0b0000,
	GIMMICK		= 0b0001,
	GOAL		= 0b0010,
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