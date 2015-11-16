#pragma once
# include "Frame/BaseScene.h"

# include "World.h"

# include "Stage/StageFactory.h"

class StageScene : public BaseScene
{
public:
	StageScene();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& render)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
private:
	std::shared_ptr<World> world;
	StageFactory m_factory;

	StageData m_currentStageData;
	StageData m_nextStageData1;
	StageData m_nextStageData2;
};
