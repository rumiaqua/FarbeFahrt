# include "MessageManager.h"

# include "Utility/SingletonFinalizer.h"
# include "Utility/String.h"

# include "Message/MessageScriptLoader.h"

# include <fstream>

MessageManager::MessageManager()
	: m_data()
	, m_canShow(false)
{

}

void MessageManager::Initialize(const std::string& indexFilename)
{
	MessageManager& instance = Singleton<MessageManager>::Instance();
	instance.m_messageDatas.clear();

	MessageScriptLoader loader;

	std::fstream stream { indexFilename };

	std::string currentDirectory = "";
	std::string buffer;

	while (std::getline(stream, buffer))
	{
		auto split = String::Split(buffer, ',');

		// カレントディレクトリの設定
		if (split[0] == "c")
		{
			currentDirectory = split[1];
			continue;
		}

		// ロード
		if (split[0] == "t")
		{
			// split[1] という名前で split[2] のファイルを読み込む
			loader.load(currentDirectory + split[2], instance.m_messageDatas[split[1]]);
		}
	}
}

void MessageManager::Add(const std::string& name)
{
	MessageManager& instance = Singleton<MessageManager>::Instance();
	instance.m_data = instance.m_messageDatas.at(name);
}

MessageData& MessageManager::Get()
{
	return Singleton<MessageManager>::Instance().m_data;
}

bool MessageManager::CanShow()
{
	MessageManager& instance = Singleton<MessageManager>::Instance();
	return instance.m_canShow && !instance.m_data.operationQueue.empty();
}

void MessageManager::SetShow(bool canShow)
{
	Singleton<MessageManager>::Instance().m_canShow = canShow;
}
