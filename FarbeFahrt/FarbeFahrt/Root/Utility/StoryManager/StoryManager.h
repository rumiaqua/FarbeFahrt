#pragma once
#include "Scene/SceneManager.h"

class StoryManager
{
public:
	StoryManager();
	void initialize();
	int getFlag();
	void setFlag(int flag);

private:
	int m_flag;
};