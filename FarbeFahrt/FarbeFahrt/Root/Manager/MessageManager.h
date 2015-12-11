# pragma once

# include <vector>

class MessageManager
{
public:

	MessageManager();

public:

	static void Add(const std::string& text);
	static std::vector<std::string> Get();
	static void Clear();
	static bool CanShow();
	static void SetShow(bool canShow);

private:

	std::vector<std::string> m_text;
	bool m_canShow;
};
