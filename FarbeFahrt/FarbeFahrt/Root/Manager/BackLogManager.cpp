# include "BackLogManager.h"
# include "Utility/SingletonFinalizer.h"

BackLogManager::BackLogManager()
	: m_backLog()
{
	m_backLog.clear();
}

void BackLogManager::Add(const std::string& message)
{
	Singleton<BackLogManager>::Instance().m_backLog.emplace_back(message);
}

std::vector<std::string> BackLogManager::GetAll()
{
	return Singleton<BackLogManager>::Instance().m_backLog;
}

std::string BackLogManager::GetRow(int index)
{
	return Singleton<BackLogManager>::Instance().m_backLog.at(index);
}

void BackLogManager::Clear()
{
	Singleton<BackLogManager>::Instance().m_backLog.clear();
}

int BackLogManager::Size()
{
	return (int)Singleton<BackLogManager>::Instance().m_backLog.size();
}
