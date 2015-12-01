#include "EndManager.h"

# include "Utility/SingletonFinalizer.h"

EndManager::EndManager()
{
	m_pattern = EndPattern::None;
}

EndManager& EndManager::instance()
{
	static EndManager& instance = Singleton<EndManager>::Instance();
	return instance;
}

void EndManager::setPattern(const EndPattern& pattern)
{
	instance().m_pattern = pattern;
}

void EndManager::setPattern(int patternNum)
{
	instance().m_pattern = (EndPattern)(patternNum + 1);
}

EndPattern EndManager::getPattern()
{
	return instance().m_pattern;
}

bool EndManager::isEnd()
{
	return instance().m_pattern != EndPattern::None;
}
