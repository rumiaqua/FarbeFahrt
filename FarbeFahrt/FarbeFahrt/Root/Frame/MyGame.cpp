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

//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�R���X�g���N�^
//�V�[���̒ǉ��A�ŏ��̃V�[���ݒ�
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
MyGame::MyGame()
	:m_breakflag(false),
	initFlag(true)
{
	m_sceneManager.addScene<GameTitle>(Scene::drawGameTitle);
	m_sceneManager.addScene<GameMenu>(Scene::drawGameMenu);
	m_sceneManager.addScene<GameMain>(Scene::drawGameMain);
	m_sceneManager.addScene<Editor>(Scene::Editor);
	m_sceneManager.addScene<StageScene>(Scene::Stage);

	// �ŏ��̃V�[���̓Q�[�����C��
	m_sceneManager.pushScene(Scene::drawGameMain);
	/*m_sceneManager.pushScene(Scene::Stage);
	m_sceneManager.pushScene(Scene::Editor);*/
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
		// �X�^�b�N����
		m_sceneManager.resolve(loader);
		loader.load();
	}
	// ���[�h���Ȃ牽�����Ȃ�
	if (loader.isLoad())
	{

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
	m_sceneManager.draw(render);
	ScreenFlip();
}