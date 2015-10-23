#include "Debug.h"

Debug::Debug()
	: m_isClear(false)
	, m_fontSize(GetFontSize())
{

}

Debug& Debug::instance()
{
	static Debug instance;
	return instance;
}

void Debug::update()
{
	if (isClear())
	{
		clear();
	}
}

void Debug::setClear(bool isClear)
{
	instance().m_isClear = isClear;
}

bool Debug::isClear()
{
	return instance().m_isClear;
}

void Debug::clear()
{
	clsDx();
}

void Debug::show(const char* message, const char* caption, UINT style)
{
	MessageBox(NULL, message, caption, style);
}

void Debug::changeFontSize(int fontSize)
{
	SetFontSize(instance().m_fontSize = fontSize);
}
