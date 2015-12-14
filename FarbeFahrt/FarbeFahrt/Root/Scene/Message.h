# pragma once

# include "Frame/BaseScene.h"
# include <vector>

struct MessageData;

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
	void processMessage();
	void renderMessage(Renderer& renderer) const;

private:

	MessageData* m_message;
	std::vector<std::string> m_textStack;

	float m_elapsedTime;
	float m_characterPerFrame;

	bool m_isStoped;

	std::string m_textureName;
	float m_elapsedFadeTime;
	float m_textureFadeFrame;
	float m_deltaFade;
	bool m_isFade;
};
