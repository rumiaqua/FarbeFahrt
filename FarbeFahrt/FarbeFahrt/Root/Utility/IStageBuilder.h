# pragma once

# include "String.h"
# include "StageData.h"

class IStageBuilder
{
public:

	virtual StageData open(const String& filename) const = 0;

	virtual void save(const String& filename, const StageData& data) const = 0;
};
