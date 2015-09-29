#pragma once
#include "Frame/BaseScene.h"

class GameMenu : public BaseScene
{
public:
	GameMenu();
	void loadContents(Loader& loader)override;
	void initialize()override;
	void update()override;
	void draw(Renderer& render)override;
	void cleanUp() override;
	~GameMenu();
};
