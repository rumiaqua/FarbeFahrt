#pragma once
#include "Utility/Def.h"
#include "Utility/String.h"
class HandleList
{
public:
	void setHandleData(const ContentMap& contentMap);
	int getHandle(const std::string& name);
	bool isLoaded(const std::string& name) const;
	bool isLoaded(const std::vector<std::string>& names) const;
	bool isLoaded(const std::unordered_map<std::string, std::string>& names) const;
	HandleList();
	~HandleList();
private:
	ContentMap m_contentMap;
};

