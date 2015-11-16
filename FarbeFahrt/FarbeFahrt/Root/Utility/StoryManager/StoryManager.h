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
	void initialize();
	bool getFlag(int flag);
	void setFlag(int flag);
	void reset(int flag);
private:
	int m_flag;
};