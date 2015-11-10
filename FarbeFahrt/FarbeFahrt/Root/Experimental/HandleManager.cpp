# include "HandleManager.h"

# include "Utility/Debug.h"

# include <algorithm>

HandleManager::HandleManager()
	: m_handles()
{

}

void HandleManager::Register(const String& name, int handle)
{
	m_handles[name] = handle;
}

int HandleManager::At(const String& name) const
{
	if (m_handles.find(name) == m_handles.end())
	{
		Debug::Show("指定された名前で登録されたハンドルはありません", "例外", MB_OK);
		return 0;
	}
	return m_handles.at(name);
}

void HandleManager::Delete(const String& name)
{
	m_handles.erase(name);
}
