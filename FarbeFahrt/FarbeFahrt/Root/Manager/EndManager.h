# pragma once

enum class EndPattern
{
	None,
	BadEnd1,
	Clear1,
	BadEnd2,
	TrueEnd,
	Clear2,
};

class EndManager
{
public:

	EndManager();

private:

	static EndManager& instance();

public:

	static void setPattern(const EndPattern& pattern);
	static void setPattern(int patternNum);
	static EndPattern getPattern();
	static bool isEnd();

private:

	EndPattern m_pattern;
};
