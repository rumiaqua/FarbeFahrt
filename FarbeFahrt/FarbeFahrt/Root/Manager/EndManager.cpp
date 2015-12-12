#include "EndManager.h"

# include "Utility/SingletonFinalizer.h"

EndManager::EndManager()
	: m_name()
{
	
}

EndManager& EndManager::instance()
{
	static EndManager& instance = Singleton<EndManager>::Instance();
	return instance;
}

void EndManager::Set(const std::string& name)
{
	instance().m_name = name;
}

std::string EndManager::Get()
{
	return instance().m_name;
}

bool EndManager::isEnd()
{
	return !instance().m_name.empty();
}
