# pragma once

# include "Frame/BaseScene.h"
# include "World.h"

class OneShotStage : public BaseScene
{
public:
	OneShotStage();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& render)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
public:
	static void load(const std::string& name);
private:
	std::shared_ptr<World> m_world;
	StageData m_data;
	static std::string m_name;
};
