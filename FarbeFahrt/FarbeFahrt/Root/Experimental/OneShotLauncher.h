# pragma once

# include "Frame/BaseScene.h"
# include "World.h"

class OneShotLauncher : public BaseScene
{
public:
	OneShotLauncher();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& render)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
private:
	void clickToStage(int key, const std::string& name);
};
