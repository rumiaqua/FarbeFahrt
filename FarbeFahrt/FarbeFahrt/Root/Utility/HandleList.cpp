#include "HandleList.h"


HandleList::HandleList()
{
}
HandleList::~HandleList()
{
}
void HandleList::setHandleData(const ContentMap& contentMap)
{
	m_contentMap = contentMap;
}
int HandleList::getHandle(const String& name)
{
	return m_contentMap.at(name.toNarrow()).handle;
}