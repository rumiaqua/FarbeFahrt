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
	initFlag(true),
	m_scene(Scene::drawGameMain)//最初に設定するシーンはここ！
{
	func.emplace(Scene::drawGameTitle, std::make_unique<GameTitle>());
	func.emplace(Scene::drawGameMenu, std::make_unique<GameMenu>());
	func.emplace(Scene::drawGameMain, std::make_unique<GameMain>());
}
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//アクセス:public
//メインループ
//引数:なし
//戻り値:なし
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
void MyGame::run()
{
	if (func[m_scene]->isChangeScene(m_scene))
	{
		if (func[m_scene]->isCleanUp())
		{
			func[m_scene]->cleanUp();
			loader.cleanUp();
		}
		func[m_scene]->refreshScene(&m_scene);
		func[m_scene]->loadContents(loader);//ここでモデル読み込もう(実際には配列に入れてるだけ)
		loader.load();
	}

	if (loader.isLoad())//読み込み中だったら
	{
		//nowLoading.draw(render);
		//読み込み中のアニメーション処理
		return;
	}

	if (loader.onCompleted())
	{
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::setSEData(loader.getSEList());
	}


	if (initFlag)//読み込みが終わった時点で一度だけ初期化
	{
		func[m_scene]->initialize();
		initFlag = false;
	}

	func[m_scene]->update();
	ClearDrawScreen();
	func[m_scene]->draw(render);
	render.draw();
	ScreenFlip();
}