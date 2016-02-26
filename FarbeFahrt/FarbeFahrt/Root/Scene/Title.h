# pragma once

# include "Frame/BaseScene.h"
#include "Utility/Point2.h"

class Title : public BaseScene
{
private:
	bool inAreaStart() const;
	bool inAreaFinish() const;
	bool isClickedStart() const;
	bool isClickedFinish() const;
	Vector2 getStartButtonPosition() const;
	Vector2 getFinishButtonPosition() const;

public:

	Title();
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& renderer)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;

private:
	bool m_startFlag;
	bool m_finishFlag;
	float m_startPosX;
	float m_finishPosX;
	Point2 m_windowSize;
	float m_alpha;
	float m_transRate;
	float m_bubblePosX;
	bool m_alphaSwitch;
};
