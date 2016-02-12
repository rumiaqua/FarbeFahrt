# pragma once

# include "StageData.h"

# include "Utility/String.h"
# include "Utility/Optional.h"

# include <unordered_map>

# include "Scene\SceneManager.h"

class World;

class StageManager
{
private:

	using Stages = std::pair<StageData, StageData>;

public:

	StageManager();

public:

	void initialize(const std::string& indexFilename);

	bool isNext() const;

	void next(World* const world);

	void apply(World* const world);

	std::string endName() const;

	bool isEnd() const;

public:

	const StageData& current() const;

	const Stages& nextStages() const;

	const std::string& bgmName() const;

	const std::unordered_map<std::string, StageData>& allStageData() const;

private:

	bool isFirst() const;

	const StageData& nextStage() const;

private:

	std::unordered_map<std::string, StageData> m_stageDatas;

	StageData m_current;

	Stages m_next;
};
