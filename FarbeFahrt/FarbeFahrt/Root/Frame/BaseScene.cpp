
#include "BaseScene.h"
static Scene saveScene = Scene::NullScene;

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::changeScene(Scene scene)
{
	saveScene = scene;
}


bool BaseScene::isChangeScene(Scene scene)
{
	if (saveScene != scene || saveScene == Scene::NullScene)//�V�[�����ς������
	{
		return true;
	}
	return false;
}

bool BaseScene::isCleanUp()
{
	if (saveScene != Scene::NullScene)//�V�[�����ς������
	{
		return true;
	}
	return false;
}

void BaseScene::refreshScene(Scene *scene)
{
	if (saveScene == Scene::NullScene)//�ŏ��̍ŏ�
	{
		saveScene = *scene;
		return;
	}
	if (saveScene != *scene)//�V�[�����ς������
	{
		*scene = saveScene;
		return;
	}
}