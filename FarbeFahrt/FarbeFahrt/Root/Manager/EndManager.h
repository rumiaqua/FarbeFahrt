# pragma once

# include <string>

class EndManager
{
public:

	EndManager();

private:

	static EndManager& instance();

public:

	static void Set(const std::string& name);
	static std::string Get();
	static bool isEnd();

private:

	std::string m_name;
};
