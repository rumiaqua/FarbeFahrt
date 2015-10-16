#include "DxLib.h"
#include "MyGame.h"
#include "Utility/Def.h"
#include <memory>
#include "Utility/Input.h"
#include "Utility/Mouse.h"
#include "Utility/Debug.h"

bool isFullScreen;
void init()
{
	SetMainWindowText("3D����");
	//�d�l�ύX���邩���H�H
	if (MessageBox(NULL, "�t���X�N���[���ŕ\�����܂����H\n�u�������v��I�������1024�~768�ɂȂ�܂�",
		"�m�F", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		SetGraphMode(nScreenSizeX, nScreenSizeY, 32);
		isFullScreen = true;
	}
	else
	{
		//�E�B���h�E���[�h
		SetGraphMode(1024,768, 32);
		isFullScreen = false;
	}

	ChangeWindowMode(!isFullScreen);
	SetUseDirect3D9Ex(TRUE);
	MV1SetUseOrigShader(TRUE);
	SetFullSceneAntiAliasingMode(4, 4);//������Ƃ��ꂢ�ɂȂ�I
	// �c�w���C�u�����̏�����
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	init();
	if (DxLib_Init() < 0)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	//�Q�[���{��
	auto myGame = std::make_unique<MyGame>();

	while (ProcessMessage() == 0 && !Input::isClicked(KEY_INPUT_ESCAPE))
	{
		ShowCursor(true);
		Input::update();
		Mouse::update();
		Debug::update();
		myGame->run();
	}
	DxLib_End();
	return 0;
}