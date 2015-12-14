# pragma once

# include "Frame/BaseScene.h"

class Title : public BaseScene
{
public:

	Title();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& render)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
};
