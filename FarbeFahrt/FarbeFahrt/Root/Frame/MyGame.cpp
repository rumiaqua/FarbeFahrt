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

//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�R���X�g���N�^
//�V�[���̒ǉ��A�ŏ��̃V�[���ݒ�
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
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
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�A�N�Z�X:public
//���C�����[�v
//����:�Ȃ�
//�߂�l:�Ȃ�
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
void MyGame::run()
{
	// �V�[���ɕύX����������
	if (m_sceneManager.hasChanged())
	{
		//�O�̃V�[���̃f�[�^�폜
		 
		// �X�^�b�N����d
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
	}

	// �X�V
	m_sceneManager.update();

	// �`��
	ClearDrawScreen();
	Debug::Println("GetASyncLoadNum : %d",GetASyncLoadNum());

	m_sceneManager.draw(render);
	render.draw();

	ScreenFlip();

	// ���㏈��
	m_sceneManager.post();
}
