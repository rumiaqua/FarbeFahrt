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
	SetMainWindowText("3Dだよ");
	//仕様変更あるかも？？
	if (MessageBox(NULL, "フルスクリーンで表示しますか？\n「いいえ」を選択すると1024×768になります",
		"確認", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		SetGraphMode(nScreenSizeX, nScreenSizeY, 32);
		isFullScreen = true;
	}
	else
	{
		//ウィンドウモード
		SetGraphMode(1024,768, 32);
		isFullScreen = false;
	}

	ChangeWindowMode(!isFullScreen);
	SetUseDirect3D9Ex(TRUE);
	MV1SetUseOrigShader(TRUE);
	SetFullSceneAntiAliasingMode(4, 4);//ちょっときれいになる！
	// ＤＸライブラリの初期化
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	init();
	if (DxLib_Init() < 0)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	//ゲーム本体
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