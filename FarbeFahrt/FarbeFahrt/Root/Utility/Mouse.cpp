#include "Mouse.h"
#include "DxLib.h"

Mouse::Mouse()
{

}

Mouse& Mouse::instance()
{
	static Mouse instance;
	return instance;
}

void Mouse::update()
{
	Mouse& ins = instance();

	int x, y;
	GetMousePoint(&x, &y);
	ins.m_position.x = x;
	ins.m_position.y = y;

	ins.m_scrollValue = GetMouseWheelRotVol();

	ins.m_previousBuffer = ins.m_currentBuffer;
	ins.m_currentBuffer = GetMouseInput();
}

POINT Mouse::Position()
{
	Mouse& ins = instance();
	return ins.m_position;
}

bool Mouse::isClicked(int mouseCode)
{
	Mouse& ins = instance();
	return
		!(ins.m_previousBuffer & mouseCode) &&
		(ins.m_currentBuffer & mouseCode);
}

bool Mouse::isPressed(int mouseCode)
{
	Mouse& ins = instance();
	return !!(ins.m_currentBuffer & mouseCode);
}

bool Mouse::isReleased(int mouseCode)
{
	Mouse& ins = instance();
	return
		(ins.m_previousBuffer & mouseCode) &&
		!(ins.m_currentBuffer & mouseCode);
}

int Mouse::scrollValue()
{
	Mouse& ins = instance();
	return ins.m_scrollValue;
}
