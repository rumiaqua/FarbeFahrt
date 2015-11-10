#pragma once
#include "Utility\Def.h"
#include "Utility\String.h"
class HandleList
{
public:
	void setHandleData(const ContentMap& contentMap);
	int getHandle(const String& name);
	HandleList();
	~HandleList();
private:
	ContentMap m_contentMap;
};

