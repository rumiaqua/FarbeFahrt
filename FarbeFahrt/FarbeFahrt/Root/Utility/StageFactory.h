# pragma once

# include "StageData.h"
# include "Vector3.h"
# include "String.h"

# include <vector>
# include <unordered_map>

class World;
class String;

class StageFactory
{
public:

	void Load(const String& filename);

	void Apply(World& world) const;

	const std::unordered_map<String, String>& Resources() const;

private:

	 StageData m_data;
};
