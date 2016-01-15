/// <summary>フェードイン専用シーン</summary>
class FadeIn final : public BaseScene
{
public:

	FadeIn(float fadeCount, bool isSwallow = false)
		: m_fadeCount(fadeCount)
		, m_currentCount(fadeCount)
		, m_isSwallow(isSwallow)
	{

	}

	virtual void loadContents(Loader& loader) override
	{
		loader.loadContent("curtain", "Texture/curtain.png");
	}

	virtual void initialize() override
	{

	}

	virtual void update() override
	{
		m_currentCount = m_currentCount - 1;

		if (m_currentCount > 0)
		{
			return;
		}

		m_manager->popScene();
	}

	virtual void draw(Renderer& renderer) override
	{
		int alpha = (int)(m_currentCount / m_fadeCount * 255);
		renderer.drawTexture("curtain", 0, 0, 0, 0, 100, 100, 0.0f,alpha);
	}

	virtual void post() override
	{

	}

	virtual void cleanUp() override
	{

	}

	virtual bool isSwallow() const override
	{
		return m_isSwallow;
	}

private:

	const float m_fadeCount;

	float m_currentCount;

	const bool m_isSwallow;
};
