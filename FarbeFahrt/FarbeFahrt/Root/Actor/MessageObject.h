# pragma once

# include "BaseActor.h"

class MessageObject : public BaseActor
{
public:
	MessageObject(IWorld& world, const std::string& name, const Vector3& position, const std::string& message);

public:
	virtual void onMessage(const std::string& message, void* parameter) override;

private:
	std::string m_message;
};
