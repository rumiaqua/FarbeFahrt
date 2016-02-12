#pragma once
#include "IWorld.h"

# include "Actor/ActorManager/ActorManager.h"
# include "Actor/Camera/Camera.h"

# include "Utility/StoryManager/StoryManager.h"

# include "Stage/StageData.h"
# include "Stage/Stage.h"

# include <string>

class World : public IWorld
{
public:
	World();
	void update();
	void draw(Renderer& renderer)const;
	virtual void addCamera(const Actor& camera);
	virtual void addActor(ActorTag tag, const Actor& actor);

	virtual Actor findActor(const std::string& name) const override;
	virtual std::vector<Actor> findActors(const std::string& name) const override;
	virtual Actor findCamera() const override;
	virtual Actor findGroup(const ActorTag& tag) const override;
	StageData getData() const;
	void apply(const StageData& data, bool isClear);
	virtual void actorSet(const std::string& actorName);
	virtual void actorSet(const Vector3& position);
	void clearActor();

private:
	Actor m_skydome;
	Actor m_camera;
	Stage m_stage;
};
