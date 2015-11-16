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
void FlagManager::Set(bool value)
{
	auto& instance = Singleton<FlagManager>::Instance().m_flags;
	for (size_t i = 0; i < instance.count(); ++i)
	{
		instance.set(i, value);
	}
}

bool FlagManager::Test(const Flag& flag)
{
	if (flag == AllFlag)
	{
		return false;
	}
	return Singleton<FlagManager>::Instance().m_flags.test(flag);
}
