#include "Mouse.h"

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

POINT Mouse::position()
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

VECTOR Mouse::screenPointToWorld(float z)
{
	MATRIX view = GetCameraViewMatrix();
	MATRIX projection = GetCameraProjectionMatrix();
	MATRIX viewport = GetCameraViewportMatrix();
	MATRIX inverse = MInverse(MMult(MMult(view, projection), viewport));
	float w = 1.0f;
	POINT pos = position();
	VECTOR in { pos.x, pos.y, z };
	VECTOR v;
	VectorTransform4(&v, &w, &in, &w, &inverse);
	v.x /= w;
	v.y /= w;
	v.z /= w;
	return v;
}
