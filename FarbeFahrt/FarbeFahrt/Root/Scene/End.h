# pragma once

# include "Frame/BaseScene.h"

/// <summary>フェードアウト専用シーン</summary>
class End final : public BaseScene
{
public:

	End();

	virtual void loadContents(Loader& loader) override;

	virtual void initialize() override;

	virtual void update() override;

	virtual void draw(Renderer& renderer) override;

	virtual void post() override;

	virtual void cleanUp() override;

	virtual bool isSwallow() const override;
};
