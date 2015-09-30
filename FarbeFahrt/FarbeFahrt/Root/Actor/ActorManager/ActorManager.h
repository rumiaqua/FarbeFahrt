#pragma once
#include "ActorTag.h"
#include "Actor/BaseActor.h"
#include <unordered_map>
class ActorManager
{
public:
	ActorManager();
	void initialize();
	void update();
	void draw(Renderer& render)const;
	void addActor(ActorTag tag, const Actor& actor);
	Actor findActor(const std::string& name);
private:
	BaseActor m_root;
	std::unordered_map<ActorTag, Actor>m_actors;
};
