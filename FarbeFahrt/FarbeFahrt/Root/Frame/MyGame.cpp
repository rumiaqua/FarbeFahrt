#include "MyGame.h"

#include "BaseScene.h"

#include "Scene/GameTitle.h"
#include "Scene/GameMenu.h"
#include "Scene/GameMain.h"
# include "Scene/Editor.h"
# include "Scene/StageScene.h"
#include "Utility\SingletonFinalizer.h"
#include "Utility\HandleList.h"
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
	m_sceneManager.addScene<Editor>(Scene::Editor);
	m_sceneManager.addScene<StageScene>(Scene::Stage);

	// 最初のシーンはゲームメイン
	m_sceneManager.pushScene(Scene::drawGameMain);
	/*m_sceneManager.pushScene(Scene::Stage);
	m_sceneManager.pushScene(Scene::Editor);*/
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
	if (loader.onCompleted())
	{
		Singleton<HandleList>::Instance().setHandleData(loader.getModelList());
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::SetData(loader.getSEList());
	}

	// 更新
	m_sceneManager.update();

	// 描画
	ClearDrawScreen();
	m_sceneManager.draw(render);
	ScreenFlip();
}