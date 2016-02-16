# pragma once

# include "Frame/BaseScene.h"
#include "Utility/Point2.h"

class TitleChoose : public BaseScene
{
public:

	TitleChoose();
	virtual ~TitleChoose();
	virtual void loadContents(Loader& loader) override;
	virtual void initialize() override;
	virtual void update() override;
	virtual void draw(Renderer& renderer) override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;

private:
	bool isPop();
	bool isChange();
	bool isYesRange();
	bool isNoRange();

private:
	bool m_yes;
	bool m_no;
	float m_yesPosX;
	float m_noPosX;
	Point2 m_texturePos;
};
