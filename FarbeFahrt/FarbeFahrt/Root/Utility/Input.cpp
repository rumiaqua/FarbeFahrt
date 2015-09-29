# include "DxLib.h"
# include "Input.h"

Input::Input()
	: m_previousBuffer()
	, m_currentBuffer()
{
}

Input& Input::instance()
{
	static Input instance;
	return instance;
}

void Input::update()
{
	Input& input = instance();
	input.m_previousBuffer = input.m_currentBuffer;
	GetHitKeyStateAll(input.m_currentBuffer.data());
}

bool Input::isClicked(int keyCode)
{
	Input& input = instance();
	return
		input.m_previousBuffer[keyCode] == 0 &&
		input.m_currentBuffer[keyCode] != 0;
}

bool Input::isPressed(int keyCode)
{
	Input& input = instance();
	return
		input.m_currentBuffer[keyCode] != 0;
}

bool Input::isReleased(int keyCode)
{
	Input& input = instance();
	return
		input.m_previousBuffer[keyCode] != 0 &&
		input.m_currentBuffer[keyCode] == 0;
}
