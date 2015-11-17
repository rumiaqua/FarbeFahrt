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

bool StoryManager::get(int flag)
{
	return (Singleton<StoryManager>::Instance().m_flag & flag) == flag;
}

void StoryManager::set(int flag)
{
	Singleton<StoryManager>::Instance().m_flag |= flag;
}

void StoryManager::reset(int flag)
{
	Singleton<StoryManager>::Instance().m_flag &= !flag;
}
