#include "MyGame.h"
#include "BaseScene.h"
#include "Scene/GameTitle.h"
#include "Scene/GameMenu.h"
#include "Scene/GameMain.h"
#include "Utility/SE.h"
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//コンストラクタ
//シーンの追加、最初のシーン設定
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
MyGame::MyGame()
	:m_breakflag(false),
	initFlag(true)
{
	m_sceneManager.addScene<GameTitle>(Scene::drawGameTitle);
	m_sceneManager.addScene<GameMenu>(Scene::drawGameMenu);
	m_sceneManager.addScene<GameMain>(Scene::drawGameMain);

	m_sceneManager.pushScene(Scene::drawGameMain);
}
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//アクセス:public
//メインループ
//引数:なし
//戻り値:なし
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
void MyGame::run()
{
	// シーンに変更があった時
	if (m_sceneManager.hasChanged())
	{
		// スタック操作
		m_sceneManager.resolve(loader);
		loader.load();
	}

	// ロード中なら何もしない
	if (loader.isLoad())
	{
		return;
	}

	// ロードが終了したら
	if (true)
		{
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::setSEData(loader.getSEList());
	}

	// 更新
	m_sceneManager.update();

	// 描画
	ClearDrawScreen();
	m_sceneManager.draw(render);
	ScreenFlip();
}