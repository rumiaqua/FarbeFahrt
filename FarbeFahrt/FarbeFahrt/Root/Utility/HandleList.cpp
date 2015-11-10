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
int HandleList::getHandle(const std::string& name)
{
	return m_contentMap[name].handle;
}