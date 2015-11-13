#pragma once
# include "Frame/BaseScene.h"

# include "World.h"

# include "Stage/StageFactory.h"

class StageScene : public BaseScene
{
public:
	StageScene();
	void loadContents(Loader& loader)override;
	void initialize()override;
	void update()override;
	void draw(Renderer& render)override;
	void cleanUp() override;
	bool isSwallow() const override;
private:
	std::shared_ptr<World> world;
	StageFactory m_factory;

	StageData m_currentStageData;
	StageData m_nextStageData;
};
