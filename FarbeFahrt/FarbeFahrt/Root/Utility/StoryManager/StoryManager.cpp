#include "StoryManager.h"

StoryManager::StoryManager()
{
	initialize();
}

void StoryManager::initialize()
{
	m_flag = 0;
}

int StoryManager::getFlag()
{
	return m_flag;
}

void StoryManager::setFlag(int flag)
{
	m_flag = flag;
}
