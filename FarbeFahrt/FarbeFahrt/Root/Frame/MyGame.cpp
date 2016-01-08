#include "MyGame.h"

#include "BaseScene.h"

# include "Scene/Scene.h"
# include "Scene/Editor.h"
# include "Scene/GameMain.h"
# include "Scene/End.h"
# include "Scene/StaffRoll.h"
# include "Scene/Message.h"
# include "Scene/Opening.h"
# include "Scene/Title.h"

# include "Experimental/ObjectViewer.h"
# include "Experimental/OneShotStage.h"
# include "Experimental/OneShotLauncher.h"

#include "Utility/SingletonFinalizer.h"
#include "Utility/HandleList.h"
#include "Utility/SE.h"
#include "Utility/BGM.h"
#include "Utility\Debug.h"

# include "Manager/MessageManager.h"

//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�R���X�g���N�^
//�V�[���̒ǉ��A�ŏ��̃V�[���ݒ�
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
MyGame::MyGame()
	:m_breakflag(false),
	initFlag(true)
{
	// Debug::SetEnabled(true);

	m_sceneManager.addScene<Editor>(Scene::Editor);
	m_sceneManager.addScene<GameMain>(Scene::GameMain);
	m_sceneManager.addScene<Opening>(Scene::Opening);
	m_sceneManager.addScene<ObjectViewer>(Scene::ObjectViewer);
	m_sceneManager.addScene<End>(Scene::End);
	m_sceneManager.addScene<StaffRoll>(Scene::StaffRoll);
	m_sceneManager.addScene<Message>(Scene::Message);
	m_sceneManager.addScene<Title>(Scene::Title);
	m_sceneManager.addScene<OneShotStage>(Scene::OneShotStage);
	m_sceneManager.addScene<OneShotLauncher>(Scene::OneShotLauncher);

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
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�A�N�Z�X:public
//���C�����[�v
//����:�Ȃ�
//�߂�l:�Ȃ�
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
void MyGame::run()
{
	if (Input::IsClicked(KEY_INPUT_F12))
	{
		Debug::SetEnabled(!Debug::IsEnabled());
	}
	if (Input::IsClicked(KEY_INPUT_F11))
	{
		Debug::SetClear(!Debug::IsClear());
	}

	// �V�[���ɕύX����������
	if (m_sceneManager.hasChanged())
	{
		//�O�̃V�[���̃f�[�^�폜
		 
		// �X�^�b�N����
		m_sceneManager.resolve(loader);

		// ���[�h
		loader.load();

		// �S���f���̃A�j���[�V����������������
		// render.refreshAnimParam();
	}

	// ���[�h���Ȃ牽�����Ȃ�
	if (loader.isLoad())
	{
		m_nowLoading.draw();
		return;
	}

	// ���[�h���I��������
	if (loader.onCompleted())
	{
		// Singleton<HandleList>::Instance().setHandleData(loader.getModelList());
		// Singleton<HandleList>::Instance().setHandleData(loader.getTextureList());
		Singleton<HandleList>::Instance().setHandleData(loader.getContentsList());
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::SetData(loader.getSEList());
		BGM::set(loader.getBGMList());
	}

	// �X�V
	m_sceneManager.update();

	// �`��
	ClearDrawScreen();
	Debug::Println("GetASyncLoadNum : %d",GetASyncLoadNum());
	Debug::Println("CanShow : %s", MessageManager::CanShow() ? "true" : "false");
	if (Input::IsPressed(KEY_INPUT_B))
	{
		BGM::play("test1");
	}
	if (Input::IsPressed(KEY_INPUT_G))
	{
		BGM::play("test2");
	}

	m_sceneManager.draw(render);
	render.draw();

	ScreenFlip();

	// ���㏈��
	m_sceneManager.post();
}
