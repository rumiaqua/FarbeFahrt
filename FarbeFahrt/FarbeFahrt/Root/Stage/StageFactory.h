# pragma once

# include "StageData.h"

# include "Utility/Vector3.h"
# include "Utility/String.h"

# include <vector>
# include <unordered_map>

class World;
class String;

class StageFactory
{
public:

	void Load(const String& filename);

	const std::unordered_map<String, String>& Resources() const;

	const StageData& Data() const;

private:

	 StageData m_data;
};
