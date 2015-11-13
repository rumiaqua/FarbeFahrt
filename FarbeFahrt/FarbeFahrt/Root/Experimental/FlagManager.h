# pragma once

# include <bitset>

enum Flag
{
	None,
	NextStage,
	AllFlag,
};

class FlagManager
{
public:

	FlagManager();

public:

	static void Set(const Flag& flag, bool value);

	static bool Test(const Flag& flag);

private:

	std::bitset<AllFlag> m_flags;
};
