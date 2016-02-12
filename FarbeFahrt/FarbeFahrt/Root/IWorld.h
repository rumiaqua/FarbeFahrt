#pragma once
#include "Actor/ActorManager/ActorTag.h"
#include "Actor/Actor.h"
#include <string>
# include <vector>
#include "Utility/Vector3.h"
//すべての始まり
//抽象インターフェース
class IWorld
{
public:
	virtual ~IWorld(){}
	virtual void addActor(ActorTag tag, const Actor& actor) = 0;
	virtual Actor findActor(const std::string& name) const = 0;
	virtual std::vector<Actor> findActors(const std::string& name) const = 0;
	virtual Actor findCamera() const = 0;
	virtual Actor findGroup(const ActorTag& tag) const = 0;
	virtual void actorSet(const std::string& actorName) = 0;
	virtual void actorSet(const Vector3& position) = 0;
};
