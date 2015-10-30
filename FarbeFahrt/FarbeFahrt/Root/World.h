#pragma once
#include "IWorld.h"

#include "Actor/ActorManager/ActorManager.h"

# include "Utility/StageData.h"

#include <string>
class World : public IWorld
{
public:
	World();
	void update();
	void draw(Renderer& render)const;
	virtual void addCamera(const Actor& camera);
	virtual void addSkydome(const Actor& sky);
	virtual void addActor(ActorTag tag, const Actor& actor);
	virtual void addField(const Actor& firld);
	virtual Actor findActor(const std::string& name)override;
	virtual Actor findCamera()override;
	virtual Actor findField()override;
	StageData getData() const;
private:
	ActorManager actors;
	Actor camera;
	Actor sky;
	Actor field;
};
