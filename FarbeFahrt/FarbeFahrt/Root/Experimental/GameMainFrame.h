#pragma once

#include "Frame/BaseScene.h"

class GameMainFrame : public BaseScene
{
public:
	GameMainFrame();
	void loadContents(Loader& loader)override;
	void initialize()override;
	void update()override;
	void draw(Renderer& render)override;
	void cleanUp() override;
	bool isSwallow() const override;

	~GameMainFrame();
};
