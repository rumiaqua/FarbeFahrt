
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
	if (saveScene != scene || saveScene == Scene::NullScene)//シーンが変わった時
	{
		return true;
	}
	return false;
}

bool BaseScene::isCleanUp()
{
	if (saveScene != Scene::NullScene)//シーンが変わった時
	{
		return true;
	}
	return false;
}

void BaseScene::refreshScene(Scene *scene)
{
	if (saveScene == Scene::NullScene)//最初の最初
	{
		saveScene = *scene;
		return;
	}
	if (saveScene != *scene)//シーンが変わった時
	{
		*scene = saveScene;
		return;
	}
}