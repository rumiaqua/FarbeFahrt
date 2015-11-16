# pragma once

# include "Utility/String.h"
# include "StageData.h"

class IStageDataBuilder
{
public:

	virtual StageData open(const String& filename) const = 0;

	virtual StageData& open(const String& filename, StageData& output) const = 0;

	virtual void save(const String& filename, const StageData& data) const = 0;
};
