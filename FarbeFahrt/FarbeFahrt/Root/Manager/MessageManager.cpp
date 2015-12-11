# include "MessageManager.h"
# include "Utility/SingletonFinalizer.h"

MessageManager::MessageManager()
	: m_text()
	, m_canShow(false)
{

}

void MessageManager::Add(const std::string& text)
{
	Singleton<MessageManager>::Instance().m_text.push_back(text);
}

std::vector<std::string> MessageManager::Get()
{
	return Singleton<MessageManager>::Instance().m_text;
}

void MessageManager::Clear()
{
	Singleton<MessageManager>::Instance().m_text.clear();
}

bool MessageManager::CanShow()
{
	MessageManager& instance = Singleton<MessageManager>::Instance();
	return
		instance.m_canShow &&
		!instance.m_text.empty();
}

void MessageManager::SetShow(bool canShow)
{
	Singleton<MessageManager>::Instance().m_canShow = canShow;
}
