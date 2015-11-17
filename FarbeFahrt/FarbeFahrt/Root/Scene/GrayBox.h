# pragma once
# include "Frame/BaseScene.h"

# include "World.h"

# include "Stage/StageFactory.h"
# include "Stage/StageManager.h"

class GrayBox : public BaseScene
{
public:
	GrayBox();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& render)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
private:
	Loader* m_loader;
	std::shared_ptr<World> m_world;
	StageManager m_stageManager;
};