#pragma once
#include "Frame/BaseScene.h"
#include "Root/World.h"
class GameMain : public BaseScene
{
public:
	GameMain();
	void loadContents(Loader& loader)override;
	void initialize()override;
	void update()override;
	void draw(Renderer& render)override;
	void cleanUp() override;

	~GameMain();
private:
	std::shared_ptr<World>world;
};
