# include "GimmickManager.h"

# include "Utility/SingletonFinalizer.h"

GimmickManager::GimmickManager()
	: m_point(0)
{
}

int GimmickManager::get()
{
	return Singleton<GimmickManager>::Instance().m_point;
}

void GimmickManager::add(unsigned int point)
{
	Singleton<GimmickManager>::Instance().m_point += point;
}

void GimmickManager::sub(unsigned int point)
{
	Singleton<GimmickManager>::Instance().m_point < point ? Singleton<GimmickManager>::Instance().m_point = 0 : Singleton<GimmickManager>::Instance().m_point -= point;
}

void GimmickManager::reset()
{
	Singleton<GimmickManager>::Instance().m_point = 0;
}
