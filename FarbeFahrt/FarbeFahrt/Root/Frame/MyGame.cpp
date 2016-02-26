#include "MyGame.h"

#include "BaseScene.h"

# include "Scene/Scene.h"
# include "Scene/GameMain.h"
# include "Scene/End.h"
# include "Scene/StaffRoll.h"
# include "Scene/Message.h"
# include "Scene/Opening.h"
# include "Scene/Title.h"
# include "Scene/BlackOut.h"
# include "Scene/BackLog.h"
#include "Utility/Mouse.h"
#include "Manager/EndManager.h"
#include "Scene/TitleChoose.h"

# include "Experimental/ObjectViewer.h"
# include "Experimental/AllResourceLoad.h"

#include "Utility/SingletonFinalizer.h"
#include "Utility/HandleList.h"
#include "Utility/SE.h"
#include "Utility/BGM.h"
#include "Utility\Debug.h"

# include "Manager/EndManager.h"

# include "Manager/MessageManager.h"

namespace
{
	const float TitleChangeTime = 2.0f;	//分
}

//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//コンストラクタ
//シーンの追加、最初のシーン設定
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
MyGame::MyGame()
	:m_breakflag(false)
	, initFlag(true)
	, m_timer(0.0f)
{
	// Debug::SetEnabled(true);

	m_sceneManager.addScene<GameMain>(Scene::GameMain);
	m_sceneManager.addScene<Opening>(Scene::Opening, &renderer);
	m_sceneManager.addScene<ObjectViewer>(Scene::ObjectViewer);
	m_sceneManager.addScene<End>(Scene::End);
	m_sceneManager.addScene<StaffRoll>(Scene::StaffRoll);
	m_sceneManager.addScene<Message>(Scene::Message);
	m_sceneManager.addScene<Title>(Scene::Title);
	m_sceneManager.addScene<AllResourceLoad>(Scene::AllResourceLoad);
	m_sceneManager.addScene<BlackOut>(Scene::BlackOut);
	m_sceneManager.addScene<BackLog>(Scene::BackLog);
	m_sceneManager.addScene<TitleChoose>(Scene::TitleChoose);

	m_sceneManager.pushScene(Scene::Title);
	// m_sceneManager.pushScene(Scene::OneShotStage);
	// m_sceneManager.pushScene(Scene::Message);
	// m_sceneManager.pushScene(Scene::ObjectViewer);
	// m_sceneManager.pushScene(Scene::End);

	Debug::SetEnabled(true);
	Debug::SetClear(true);

	MessageManager::Initialize("Resources/Script/Message/index.csv");

	loader.loadContent("test1", "Sound/BGM/bad_end.mp3");
	loader.loadContent("test2", "Sound/BGM/end2.mp3");
}
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//アクセス:public
//メインループ
//引数:なし
//戻り値:なし
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
void MyGame::run()
{
	checkNotOperation() ? m_timer++ : m_timer = 0;

	if (m_timer >= TitleChangeTime * 60.0f * 60.0f)
	{
		m_timer = 0;
		m_sceneManager.changeScene(Scene::Title);
	}

	// シーンに変更があった時
	if (m_sceneManager.hasChanged())
	{
		//前のシーンのデータ削除

		// スタック操作
		m_sceneManager.resolve(loader);

		// ロード
		loader.load();

		// 全モデルのアニメーションを初期化する
		// renderer.refreshAnimParam();
	}

	// ロード中なら何もしない
	if (loader.isLoad())
	{
		m_nowLoading.draw(renderer);
		return;
	}

	// ロードが終了したら
	if (loader.onCompleted())
	{
		// Singleton<HandleList>::Instance().setHandleData(loader.getModelList());
		// Singleton<HandleList>::Instance().setHandleData(loader.getTextureList());
		Singleton<HandleList>::Instance().setHandleData(loader.getContentsList());
		renderer.setModelData(loader.getModelList());
		renderer.setTextureData(loader.getTextureList());
		SE::SetData(loader.getSEList());
		BGM::set(loader.getBGMList());
	}

	if (Input::IsClicked(KEY_INPUT_F1))
	{
		m_sceneManager.pushScene(Scene::AllResourceLoad);
	}
	if (Input::IsClicked(KEY_INPUT_F2))
	{
		Debug::SetEnabled(!Debug::IsEnabled());
	}
	if (Input::IsClicked(KEY_INPUT_F3))
	{
		m_sceneManager.changeScene(Scene::Title);
	}

	Debug::Println("DebugMode");
	Debug::Println("F1 : AllResourceLoad");
	Debug::Println("F2 : Debug Toggle");
	Debug::Println("F3 : Goto Title");

	Debug::Println(String::Create("TitleChange", m_timer));

	// 更新
	m_sceneManager.update();

	// 描画
	ClearDrawScreen();
	/*Debug::Println("GetASyncLoadNum : %d",GetASyncLoadNum());
	Debug::Println("CanShow : %s", MessageManager::CanShow() ? "true" : "false");*/

	m_sceneManager.draw(renderer);
	renderer.draw();

	ScreenFlip();

	// 事後処理
	m_sceneManager.post();
}

bool MyGame::isEnd() const
{
	return m_sceneManager.isEmpty();
}

bool MyGame::checkNotOperation()
{
	EndManager endManager;
	return !CheckHitKeyAll() && !GetMouseInput() && !Mouse::ScrollValue() && !m_sceneManager.hasChanged() && !loader.isLoad() && !m_sceneManager.isNowStaffRoll();
}
