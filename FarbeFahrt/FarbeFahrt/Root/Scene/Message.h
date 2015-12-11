# pragma once

# include "Frame/BaseScene.h"
# include <vector>

/// <summary>メッセージシーン</summary>
class Message final : public BaseScene
{
public:

	Message();

	virtual void loadContents(Loader& loader) override;

	virtual void initialize() override;

	virtual void update() override;

	virtual void draw(Renderer& renderer) override;

	virtual void post() override;

	virtual void cleanUp() override;

	virtual bool isSwallow() const override;

private:

	unsigned int getLengthMessage() const;

private:

	std::vector<std::string> m_message;

	float m_elapsedTime;

	float m_characterPerFrame;
};
