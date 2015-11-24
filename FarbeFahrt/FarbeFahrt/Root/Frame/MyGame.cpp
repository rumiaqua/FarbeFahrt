#include "MyGame.h"

#include "BaseScene.h"

# include "Scene/Editor.h"
# include "Scene/GrayBox.h"

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

	// 最初のシーンはゲームメイン
	m_sceneManager.pushScene(Scene::GrayBox);

	// 必ず読むリソース
	// とりあえずここにおいておく
	loader.loadContent("sky", "Model/skydome/昼の月.x");
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
		// loader.cleanUp();
		// スタック操作
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
		Singleton<HandleList>::Instance().setHandleData(loader.getModelList());
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::SetData(loader.getSEList());
	}

	// 更新
	m_sceneManager.update();

	// 描画
	ClearDrawScreen();
	Debug::Println("%d",GetASyncLoadNum());
	m_sceneManager.draw(render);
	render.draw();
	ScreenFlip();

	// 事後処理
	m_sceneManager.post();
}
