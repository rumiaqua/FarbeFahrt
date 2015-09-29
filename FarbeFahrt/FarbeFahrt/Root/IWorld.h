#pragma once
#include "Actor/ActorManager/ActorTag.h"
#include "Actor/Actor.h"
#include <string>
//すべての始まり
//抽象インターフェース
class IWorld
{
public:
	virtual ~IWorld(){}
	virtual void addActor(ActorTag tag, const Actor& actor) = 0;
	virtual Actor findActor(const std::string& name) = 0;
	virtual Actor findCamera() = 0;
	virtual Actor findField() = 0;
};