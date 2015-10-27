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

	//if (func[m_scene]->isChangeScene(m_scene))
	//{
	//	if (func[m_scene]->isCleanUp())
	//	{
	//		func[m_scene]->cleanUp();
	//		loader.cleanUp();
	//	}
	//	func[m_scene]->refreshScene(&m_scene);
	//	func[m_scene]->loadContents(loader);//ここでモデル読み込もう(実際には配列に入れてるだけ)
	//	loader.load();
	//}
	//render.setModelData(loader.getModelList());
	//render.setTextureData(loader.getTextureList());
	//SE::setSEData(loader.getSEList());

	//if (loader.isLoad())//読み込み中だったら
	//{
	//	//nowLoading.draw(render);
	//	//読み込み中のアニメーション処理
	//	return;
	//}
	//else
	//{
	//	if (initFlag)//読み込みが終わった時点で一度だけ初期化
	//	{
	//		func[m_scene]->initialize();
	//		initFlag = false;
	//	}
	//}
	//func[m_scene]->update();
	//ClearDrawScreen();
	//func[m_scene]->draw(render);
	//render.draw();
	//ScreenFlip();
}