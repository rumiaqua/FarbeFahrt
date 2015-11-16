# include "StageFactory.h"

# include "World.h"

# include "ScriptStageDataBuilder.h"

void StageFactory::Load(const String& filename)
{
	ScriptStageDataBuilder builder;

	builder.open(filename, m_data);
}

void StageFactory::Load(const String& filename, StageData& output)
{
	ScriptStageDataBuilder().open(filename, output);
}

const std::unordered_map<String, String>& StageFactory::Resources() const
{
	return m_data.resourceList;
}

const StageData& StageFactory::Data() const
{
	return m_data;
}
