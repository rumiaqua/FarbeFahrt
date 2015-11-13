# include "FlagManager.h"

# include "Utility/SingletonFinalizer.h"

FlagManager::FlagManager()
	: m_flags()
{

}

void FlagManager::Set(const Flag& flag, bool value)
{
	Singleton<FlagManager>::Instance().m_flags.set(flag, value);
}

bool FlagManager::Test(const Flag& flag)
{
	if (flag == AllFlag)
	{
		return false;
	}
	return Singleton<FlagManager>::Instance().m_flags.test(flag);
}
