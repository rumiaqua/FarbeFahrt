#include "DxLib.h"
#include "MyGame.h"
#include "Utility/Def.h"
#include <memory>
#include "Utility/Input.h"
#include "Utility/Mouse.h"
#include "Utility/Debug.h"
# include "Utility/SingletonFinalizer.h"

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

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(true);
	SetUseDirect3D9Ex(TRUE);
	MV1SetUseOrigShader(TRUE);
	SetAlwaysRunFlag(TRUE);
	//SetFullSceneAntiAliasingMode(4, 4);//ちょっときれいになる！
	// ＤＸライブラリの初期化
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	init();
	if (DxLib_Init() < 0)
	{
		return -1;
	}
	SetMouseDispFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);
	//ゲーム本体
	auto myGame = std::make_unique<MyGame>();

	while (
		ProcessMessage() == 0)
	{
		ShowCursor(true);
		Input::Update();
		Mouse::Update();
		Debug::Update();
		myGame->run();
		if (myGame->isEnd())
		{
			break;
		}
	}
	SingletonFinalizer::Finalize();
	DxLib_End();
	return 0;
}