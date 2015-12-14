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
	static void Clear();
	static bool isEnd();
	static void SetEnd(bool canEnd);
	static bool CanEnd();
	static void SetShowStaffRoll(bool showStaffRoll);
	static bool IsShowStaffRoll();

private:

	std::string m_name;
	bool m_canEnd;
	bool m_isShowStaffRoll;
};
