
#include "BaseScene.h"

BaseScene::BaseScene()
	: m_manager(nullptr)
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::setManagerPtr(ISceneMediator* const mediator)
{
	m_manager = mediator;
}
