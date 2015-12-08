# pragma once

# include "Frame/BaseScene.h"

/// <summary>スタッフロールシーン</summary>
class StaffRoll final : public BaseScene
{
public:

	StaffRoll();

	virtual void loadContents(Loader& loader) override;

	virtual void initialize() override;

	virtual void update() override;

	virtual void draw(Renderer& renderer) override;

	virtual void post() override;

	virtual void cleanUp() override;

	virtual bool isSwallow() const override;

private:

	float m_elapsedTime;

	const float m_needTime;
};
