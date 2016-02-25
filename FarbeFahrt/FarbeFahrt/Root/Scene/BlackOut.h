#pragma once
# include "Frame/BaseScene.h"
# include "Utility\Renderer.h"
class BlackOut : public BaseScene
{
public:
	BlackOut();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& renderer)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
private:
	bool m_once;
};

