#pragma once
#include "IWorld.h"

#include "Actor/ActorManager/ActorManager.h"
#include "Utility/StoryManager/StoryManager.h"

#include "Stage/StageData.h"

# include "Stage/Stage.h"
# include "Actor/Camera/Camera.h"

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

	virtual Actor findActor(const std::string& name) const override;
	virtual Actor findCamera() const override;
	virtual Actor findField() const override;
	StageData getData() const;
	virtual void initFlag();
	virtual int getFlag();
	virtual void setFlag(int flag);
	void apply(const StageData& data);
	virtual void actorSet(const std::string& actorName);

private:
	StoryManager m_storymanager;
	Actor m_skydome;
	Actor m_camera;
	Stage m_stage;
};
