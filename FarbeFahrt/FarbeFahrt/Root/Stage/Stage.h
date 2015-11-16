# pragma once

# include "Actor/ActorManager/ActorManager.h"
# include "StageData.h"

class World;

class Stage
{
public:

	Stage(World* world);

public:

	void apply(const StageData& data, bool isClear = true);

	void update();

	void draw(Renderer& renderer) const;

	void addActor(const ActorTag& tag, const Actor& actor);

	Actor findActor(const std::string& name) const;

	Actor findField() const;

	void clearActor();

private:

	World* m_world;

	Actor m_field;

	ActorManager m_actorManager;
};
