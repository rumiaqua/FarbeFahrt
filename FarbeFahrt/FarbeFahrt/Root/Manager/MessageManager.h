# pragma once

# include "Message/MessageData.h"

# include <unordered_map>

class MessageManager
{
public:

	MessageManager();

public:

	static void Initialize(const std::string& indexFilename);
	static void Add(const std::string& name);
	static MessageData& Get();
	static bool CanShow();
	static void SetShow(bool canShow);

private:

	std::unordered_map<std::string, MessageData> m_messageDatas;
	MessageData m_data;
	bool m_canShow;
};
