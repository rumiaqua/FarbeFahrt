# pragma once

# include "Frame/BaseScene.h"

/// <summary>�t�F�[�h�A�E�g��p�V�[��</summary>
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
