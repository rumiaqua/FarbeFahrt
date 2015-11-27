# pragma once

# include "Utility/String.h"
# include "StageData.h"

class IStageDataBuilder
{
public:

	virtual StageData open(const std::string& filename) const = 0;

	virtual StageData& open(const std::string& filename, StageData& output) const = 0;

	virtual void save(const std::string& filename, const StageData& data) const = 0;
};
