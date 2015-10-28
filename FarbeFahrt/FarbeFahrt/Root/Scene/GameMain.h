#pragma once
#include "Frame/BaseScene.h"
#include "World.h"
class GameMain : public BaseScene
{
public:
	GameMain();
	void loadContents(Loader& loader)override;
	void initialize()override;
	void update()override;
	void draw(Renderer& render)override;
	void cleanUp() override;
	bool isSwallow() const override;

	~GameMain();
private:
	std::shared_ptr<World>world;
};
