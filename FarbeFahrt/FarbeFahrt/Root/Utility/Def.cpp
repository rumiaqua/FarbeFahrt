#include "Def.h"

RECT System::GetWindowRect()
{
	RECT rect;
	GetWindowCRect(&rect);
	return rect;
}
int System::GetWindowWidth()
{
	RECT&& rect = GetWindowRect();
	return rect.right - rect.left;
}
int System::GetWindowHeight()
{
	RECT&& rect = GetWindowRect();
	return rect.bottom - rect.top;
}