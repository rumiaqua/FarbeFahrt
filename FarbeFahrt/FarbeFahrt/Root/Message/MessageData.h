# pragma once

# include "MessageOperation.h"

# include <queue>

struct MessageData
{
public:

	MessageData();

public:

	void add(const std::string& operation, const std::string& message);
	MessageOperation pop();
	bool empty() const;

public:

	std::queue<MessageOperation> operationQueue;
};
