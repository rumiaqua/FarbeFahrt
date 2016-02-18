# pragma once

# include "BaseActor.h"

class Accessory : public BaseActor
{
public:

	Accessory(IWorld& world);
	virtual void onMessage(const std::string& message, void* parameter) override;

private:

	Actor m_herb;
	Actor m_medicine;
	Actor m_elder;
};
