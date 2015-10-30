# include "DxLib.h"
# include "Input.h"

Input::Input()
	: m_previousBuffer()
	, m_currentBuffer()
{
}

Input& Input::Instance()
{
	static Input instance;
	return instance;
}

void Input::Update()
{
	Input& input = Instance();
	input.m_previousBuffer = input.m_currentBuffer;
	GetHitKeyStateAll(input.m_currentBuffer.data());
}

bool Input::IsClicked(int keyCode)
{
	Input& input = Instance();
	return
		input.m_previousBuffer[keyCode] == 0 &&
		input.m_currentBuffer[keyCode] != 0;
}

bool Input::IsPressed(int keyCode)
{
	Input& input = Instance();
	return
		input.m_currentBuffer[keyCode] != 0;
}

bool Input::IsReleased(int keyCode)
{
	Input& input = Instance();
	return
		input.m_previousBuffer[keyCode] != 0 &&
		input.m_currentBuffer[keyCode] == 0;
}
