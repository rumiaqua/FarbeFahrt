# pragma once

# include "StageData.h"

# include "Utility/Vector3.h"
# include "Utility/String.h"

# include <vector>
# include <unordered_map>

class World;


class StageFactory
{
public:

	void Load(const std::string& filename);

	void Load(const std::string& filename, StageData& output);

	const std::unordered_map<std::string, std::string>& Resources() const;

	const StageData& Data() const;

private:

	 StageData m_data;
};
