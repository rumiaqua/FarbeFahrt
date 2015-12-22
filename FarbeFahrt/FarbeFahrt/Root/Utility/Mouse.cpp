#include "Mouse.h"
# include "Matrix.h"

# include <DxLib.h>

Mouse::Mouse()
{
}

Mouse& Mouse::Instance()
{
	static Mouse instance;
	return instance;
}

void Mouse::Update()
{
	Mouse& ins = Instance();

	int x, y;
	GetMousePoint(&x, &y);
	ins.m_position.x = x;
	ins.m_position.y = y;

	ins.m_scrollValue = GetMouseWheelRotVol();

	ins.m_previousBuffer = ins.m_currentBuffer;
	ins.m_currentBuffer = GetMouseInput();
}

Point2 Mouse::Position()
{
	Mouse& ins = Instance();
	return ins.m_position;
}

bool Mouse::IsClicked(int mouseCode)
{
	Mouse& ins = Instance();
	return
		!(ins.m_previousBuffer & mouseCode) &&
		(ins.m_currentBuffer & mouseCode);
}

bool Mouse::IsPressed(int mouseCode)
{
	Mouse& ins = Instance();
	return !!(ins.m_currentBuffer & mouseCode);
}

bool Mouse::IsReleased(int mouseCode)
{
	Mouse& ins = Instance();
	return
		(ins.m_previousBuffer & mouseCode) &&
		!(ins.m_currentBuffer & mouseCode);
}

int Mouse::ScrollValue()
{
	Mouse& ins = Instance();
	return ins.m_scrollValue;
}

Vector3 Mouse::PositionValue()
{
	Mouse& ins = Instance();
	return Vector3::Zero();
}

Vector3 Mouse::ScreenPointToWorld(float z)
{
	Matrix view = GetCameraViewMatrix();
	Matrix projection = GetCameraProjectionMatrix();
	Matrix viewport = GetCameraViewportMatrix();
	Matrix inverse = (view * projection * viewport).inversed();
	Point2 pos = Position();
	Vector4 v = Vector4(static_cast<float>(pos.x), static_cast<float>(pos.y), z, 1.0f) * inverse;
	v.x /= v.w;
	v.y /= v.w;
	v.z /= v.w;
	return Vector3(v);
}
