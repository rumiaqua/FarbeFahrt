# pragma once

# include "BaseActor.h"

class Book : public BaseActor
{
public:

	Book(IWorld& world, const Vector3& position)
		: BaseActor(world, "Book", position, Matrix::identity(), nullptr)
	{
		
	}

	virtual void onMessage(const String& message, void* parameter) override
	{
		if (message == "TurnOver")
		{
			turnOver();
		}

		BaseActor::onMessage(message, parameter);
	}

private:

	void turnOver()
	{
		m_currentPage->sendMessage("startAnimation", nullptr);
		m_nextPage->sendMessage("startAnimation", nullptr);
	}

private:

	Actor m_currentPage;
	Actor m_nextPage;
};
