# include "StoryManager.h"

# include "Utility/SingletonFinalizer.h"

StoryManager::StoryManager()
	: m_flag(NONE)
{

}

void StoryManager::initialize()
{
	Singleton<StoryManager>::Instance().m_flag = NONE;
}

bool StoryManager::get(unsigned int flag)
{
	return (Singleton<StoryManager>::Instance().m_flag & flag) == flag;
}

void StoryManager::set(unsigned int flag)
{
	Singleton<StoryManager>::Instance().m_flag |= flag;
}

void StoryManager::reset(unsigned int flag)
{
	Singleton<StoryManager>::Instance().m_flag &= ~flag;
}
