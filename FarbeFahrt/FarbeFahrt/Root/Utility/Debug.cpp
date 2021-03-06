#include "Debug.h"

Debug::Debug()
	: m_isEnabled(false)
	, m_isClear(false)
	, m_fontSize(GetFontSize())
{

}

Debug& Debug::Instance()
{
	static Debug instance;
	return instance;
}

void Debug::SetEnabled(bool isEnabled)
{
	Instance().m_isEnabled = isEnabled;
}

bool Debug::IsEnabled()
{
	return Instance().m_isEnabled;
}

void Debug::Update()
{
	if (IsClear())
	{
		Clear();
	}
}

void Debug::SetClear(bool isClear)
{
	Instance().m_isClear = isClear;
}

bool Debug::IsClear()
{
	return Instance().m_isClear;
}

void Debug::Clear()
{
	if (!IsEnabled())
	{
		return;
	}
	clsDx();
}

void Debug::Show(const char* message, const char* caption, UINT style)
{
	MessageBox(NULL, message, caption, style);
}

void Debug::ChangeFontSize(int fontSize)
{
	SetFontSize(Instance().m_fontSize = fontSize);
}
