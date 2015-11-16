#include "StoryManager.h"

StoryManager::StoryManager()
{
	initialize();
}

void StoryManager::initialize()
{
	m_flag = NONE;
}

bool StoryManager::getFlag(int flag)
{
	return (m_flag & flag) == flag;
}

void StoryManager::setFlag(int flag)
{
	m_flag |= flag;
}

void StoryManager::reset(int flag)
{
	m_flag &= !flag;
}
