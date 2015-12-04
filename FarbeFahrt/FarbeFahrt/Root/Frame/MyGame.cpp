#include "MyGame.h"

#include "BaseScene.h"

# include "Scene/Editor.h"
# include "Scene/GrayBox.h"
# include "Scene/End.h"
# include "Scene/StaffRoll.h"

# include "Experimental/ObjectViewer.h"

#include "Utility/SingletonFinalizer.h"
#include "Utility/HandleList.h"
#include "Utility/SE.h"

#include "Utility\Debug.h"

//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//コンストラクタ
//シーンの追加、最初のシーン設定
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
MyGame::MyGame()
	:m_breakflag(false),
	initFlag(true)
{
	m_sceneManager.addScene<Editor>(Scene::Editor);
	m_sceneManager.addScene<GrayBox>(Scene::GrayBox);

	m_sceneManager.addScene<ObjectViewer>(Scene::ObjectViewer);
	m_sceneManager.addScene<End>(Scene::End);
	m_sceneManager.addScene<StaffRoll>(Scene::StaffRoll);

	m_sceneManager.pushScene(Scene::GrayBox);
	// m_sceneManager.pushScene(Scene::ObjectViewer);
	// m_sceneManager.pushScene(Scene::End);
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
		//前のシーンのデータ削除
		 
		// スタック操作d
		m_sceneManager.resolve(loader);

		// ロード
		loader.load();

		// 全モデルのアニメーションを初期化する
		// render.refreshAnimParam();
	}

	// ロード中なら何もしない
	if (loader.isLoad())
	{
		m_nowLoading.draw();
		return;
	}

	// ロードが終了したら
	if (loader.onCompleted())
	{
		// Singleton<HandleList>::Instance().setHandleData(loader.getModelList());
		// Singleton<HandleList>::Instance().setHandleData(loader.getTextureList());
		Singleton<HandleList>::Instance().setHandleData(loader.getContentsList());
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::SetData(loader.getSEList());
	}

	// 更新
	m_sceneManager.update();

	// 描画
	ClearDrawScreen();
	Debug::Println("GetASyncLoadNum : %d",GetASyncLoadNum());

	m_sceneManager.draw(render);
	render.draw();

	ScreenFlip();

	// 事後処理
	m_sceneManager.post();
}
