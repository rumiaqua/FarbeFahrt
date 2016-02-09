# pragma once

# include "Frame/BaseScene.h"

class BackLog : public BaseScene
{
public:

	BackLog();
	virtual ~BackLog();
	virtual void loadContents(Loader& loader) override;
	virtual void initialize() override;
	virtual void update() override;
	virtual void draw(Renderer& renderer) override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;

private:

	int m_currentRow;
};
