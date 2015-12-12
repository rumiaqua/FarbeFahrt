# include "MessageData.h"

# include "MessageOperation.h"

MessageData::MessageData()
{

}

void MessageData::add(const std::string& operation, const std::string& message)
{
	operationQueue.emplace(operation, message);
}

MessageOperation MessageData::pop()
{
	MessageOperation& op = operationQueue.front();
	std::string operation = op.operation;
	std::string message = op.message;
	operationQueue.pop();
	return { operation, message };
}

bool MessageData::empty() const
{
	return operationQueue.empty();
}
