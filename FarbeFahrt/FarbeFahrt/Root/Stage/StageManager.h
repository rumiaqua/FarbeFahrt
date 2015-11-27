# pragma once

# include "StageData.h"

# include "Utility/String.h"

class World;

class StageManager
{
private:

	using Stages = std::pair<StageData, StageData>;

public:

	StageManager(const std::string& firstStageName);

public:

	bool isNext() const;

	void next(World* const world);

	void apply(World* const world);

public:

	const StageData& current() const;

	const Stages& nextStages() const;

private:

	bool isFirst() const;

	const StageData& nextStage() const;

private:

	StageData m_current;

	Stages m_next;
};
