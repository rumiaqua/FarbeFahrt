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
	virtual Actor findActor(const std::string& name) const = 0;
	virtual Actor findCamera() const = 0;
	virtual Actor findField() const = 0;
	virtual void initFlag() = 0;
	virtual int getFlag() = 0;
	virtual void setFlag(int flag) = 0;
};
