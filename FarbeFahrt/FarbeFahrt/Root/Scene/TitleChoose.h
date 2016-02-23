# pragma once

# include "Frame/BaseScene.h"
#include "Utility/Point2.h"
# include "Utility/Optional.h"

class TitleChoose : public BaseScene
{
public:
	enum class State
	{
		FadeIn,
		Wait,
		FadeOut,
	};

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
	float textureHeightPos();
	float yesWidthPos();
	float noWidthPos();

private:
	bool inAreaYes() const;
	bool inAreaNo() const;
	bool isClickedYes() const;
	bool isClickedNo() const;
	Vector2 getYesButtonPosition() const;
	Vector2 getNoButtonPosition() const;
	void fadeIn();
	void wait();
	void fadeOut();

private:
	bool m_yesFlag;
	bool m_noFlag;
	float m_yesPosX;
	float m_noPosX;
	Point2 m_windowSize;

	State m_state;
	float m_elapsedTime;
	Optional<bool> m_isYesSelected;
};
