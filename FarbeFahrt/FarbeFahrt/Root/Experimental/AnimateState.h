# pragma once

# include <string>

struct AnimateState
{
	std::string name;
	bool isReversed;
	AnimateState(const std::string& name, bool isReversed);
};
