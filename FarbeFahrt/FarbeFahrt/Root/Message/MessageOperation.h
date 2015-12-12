# pragma once

# include <string>

struct MessageOperation
{
	std::string operation;
	std::string message;
	MessageOperation(const std::string& operation, const std::string& message);
};
