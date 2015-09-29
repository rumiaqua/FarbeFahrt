#pragma once
#include "Actor/ActorManager/ActorTag.h"
#include "Actor/Actor.h"
#include <string>
//���ׂĂ̎n�܂�
//���ۃC���^�[�t�F�[�X
class IWorld
{
public:
	virtual ~IWorld(){}
	virtual void addActor(ActorTag tag, const Actor& actor) = 0;
	virtual Actor findActor(const std::string& name) = 0;
	virtual Actor findCamera() = 0;
	virtual Actor findField() = 0;
};