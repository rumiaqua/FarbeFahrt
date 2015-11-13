# include "StageFactory.h"

# include "World.h"

# include "IStageBuilder.h"
# include "ScriptStageBuilder.h"

void StageFactory::Load(const String& filename)
{
	ScriptStageBuilder builder;

	m_data = builder.open(filename);
}

const std::unordered_map<String, String>& StageFactory::Resources() const
{
	return m_data.resourceList;
}

const StageData& StageFactory::Data() const
{
	return m_data;
}
