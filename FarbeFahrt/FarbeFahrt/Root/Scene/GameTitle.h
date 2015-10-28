#pragma once
#include "Frame/BaseScene.h"
class GameTitle : public BaseScene
{
public:
	GameTitle();
	void loadContents(Loader& loader)override;
	void initialize()override;
	void update()override;
	void draw(Renderer& render)override;
	void cleanUp() override;
	bool isSwallow() const override;
	~GameTitle();
};
