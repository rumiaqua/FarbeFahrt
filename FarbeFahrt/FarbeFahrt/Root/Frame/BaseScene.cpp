
#include "BaseScene.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::setManagerPtr(ISceneMediator* const mediator)
{
	m_manager = mediator;
}
