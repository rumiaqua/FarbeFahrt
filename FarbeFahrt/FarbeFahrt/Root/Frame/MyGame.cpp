#include "MyGame.h"

#include "BaseScene.h"

# include "Scene/Editor.h"
# include "Scene/GrayBox.h"

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

	// �ŏ��̃V�[���̓Q�[�����C��
	m_sceneManager.pushScene(Scene::GrayBox);

	// �K���ǂރ��\�[�X
	// �Ƃ肠���������ɂ����Ă���
	loader.loadContent("sky", "Model/skydome/���̌�.x");
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
		// loader.cleanUp();
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
		Singleton<HandleList>::Instance().setHandleData(loader.getModelList());
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::SetData(loader.getSEList());
	}

	// �X�V
	m_sceneManager.update();

	// �`��
	ClearDrawScreen();
	Debug::Println("%d",GetASyncLoadNum());
	m_sceneManager.draw(render);
	render.draw();
	ScreenFlip();

	// ���㏈��
	m_sceneManager.post();
}
