#pragma once
#include "Frame/BaseScene.h"
#include <array>
#include <string>
class Prologue :
	public BaseScene
{
public:
	Prologue();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& renderer)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
private:
	std::array<std::string, 3> textures;
	int m_texNum;
	int m_timer;
};

