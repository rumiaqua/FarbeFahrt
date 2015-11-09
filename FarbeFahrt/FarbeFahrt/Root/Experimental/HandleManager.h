# pragma once

# include "Utility/String.h"

# include <unordered_map>

class HandleManager
{
public:

	HandleManager();

public:

	void Register(const String& name, int handle);

	int At(const String& name) const;

	void Delete(const String& name);

private:

	std::unordered_map<String, int> m_handles;
};
