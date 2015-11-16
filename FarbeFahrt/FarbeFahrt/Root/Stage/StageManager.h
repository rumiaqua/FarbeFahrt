# pragma once

# include "StageData.h"

# include "Utility/String.h"

class World;

class StageManager
{
public:

	StageManager(const String& firstStageName);

public:

	bool isNext() const;

	void next(World* const world);

	void apply(World* const world);

public:

	const StageData& current() const;

private:

	bool isFirst() const;

	const StageData& nextStage() const;

private:

	using Stages = std::pair<StageData, StageData>;

	StageData m_current;

	Stages m_next;
};
