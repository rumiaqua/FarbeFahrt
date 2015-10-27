#include "MyGame.h"
#include "BaseScene.h"
#include "Scene/GameTitle.h"
#include "Scene/GameMenu.h"
#include "Scene/GameMain.h"
#include "Utility/SE.h"
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�R���X�g���N�^
//�V�[���̒ǉ��A�ŏ��̃V�[���ݒ�
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
MyGame::MyGame()
	:m_breakflag(false),
	initFlag(true),
	m_scene(Scene::drawGameMain)//�ŏ��ɐݒ肷��V�[���͂����I
{
	func.emplace(Scene::drawGameTitle, std::make_unique<GameTitle>());
	func.emplace(Scene::drawGameMenu, std::make_unique<GameMenu>());
	func.emplace(Scene::drawGameMain, std::make_unique<GameMain>());
}
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�A�N�Z�X:public
//���C�����[�v
//����:�Ȃ�
//�߂�l:�Ȃ�
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
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
		func[m_scene]->loadContents(loader);//�����Ń��f���ǂݍ�����(���ۂɂ͔z��ɓ���Ă邾��)
		loader.load();
	}

	if (loader.isLoad())//�ǂݍ��ݒ���������
	{
		//nowLoading.draw(render);
		//�ǂݍ��ݒ��̃A�j���[�V��������
		return;
	}

	if (loader.onCompleted())
	{
		render.setModelData(loader.getModelList());
		render.setTextureData(loader.getTextureList());
		SE::setSEData(loader.getSEList());
	}


	if (initFlag)//�ǂݍ��݂��I��������_�ň�x����������
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