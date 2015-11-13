# pragma once

# include "StageData.h"

# include "Experimental/FlagManager.h"

# include <vector>

class StageManager
{
public:

	StageManager()
	{

	}

public:

	bool isNext()
	{
		return FlagManager::Test(Flag::NextStage);
	}

	void next()
	{
		if (!isNext())
		{
			return;
		}
	}

private:

	StageData m_current;

	std::vector<StageData> m_nextDatas;
};
