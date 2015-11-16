# include "StageManager.h"

# include "StageFactory.h"

# include "World.h"

# include "Utility/SingletonFinalizer.h"
# include "Utility/StoryManager/StoryManager.h"

StageManager::StageManager(const String& firstStageName)
	: m_current()
	, m_next()
{
	StageFactory().Load(firstStageName, m_current);
}

bool StageManager::isNext() const
{
	return StoryManager::get(BitFlag::GOAL);
}

void StageManager::next(World* const world)
{
	
	m_current = nextStage();
	apply(world);
	StoryManager::initialize();
}

void StageManager::apply(World* const world)
{
	world->apply(m_current, true);
	StageFactory().Load(m_current.nextStage.first, m_next.first);
	StageFactory().Load(m_current.nextStage.second, m_next.second);
}

const StageData& StageManager::current() const
{
	return m_current;
}

bool StageManager::isFirst() const
{
	return StoryManager::get(BitFlag::GIMMICK);
}

const StageData& StageManager::nextStage() const
{
	return isFirst() ? m_next.first : m_next.second;
}
