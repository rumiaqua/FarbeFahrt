#include "Debug.h"

Debug::Debug()
	: m_isClear(false)
	, m_fontSize(GetFontSize())
{

}

Debug& Debug::Instance()
{
	static Debug instance;
	return instance;
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
