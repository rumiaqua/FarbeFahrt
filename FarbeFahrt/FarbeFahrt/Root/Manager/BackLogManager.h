# pragma once

# include <string>
# include <vector>

class BackLogManager
{
public:

	BackLogManager();

public:

	static void Add(const std::string& message);
	static std::vector<std::string> GetAll();
	static std::string GetRow(int index);
	static void Clear();
	static int Size();
private:

	std::vector<std::string> m_backLog;
};
