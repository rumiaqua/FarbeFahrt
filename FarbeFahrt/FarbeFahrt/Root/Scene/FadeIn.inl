/// <summary>�t�F�[�h�C����p�V�[��</summary>
class FadeIn final : public BaseScene
{
public:

	FadeIn(float fadeCount, bool isSwallow = false)
		: m_fadeCount(fadeCount)
		, m_currentCount(fadeCount)
		, m_isSwallow(isSwallow)
	{

	}

	void loadContents(Loader& loader) override
	{
		loader.loadContent("curtain", "Texture/curtain.png");
	}

	void initialize() override
	{

	}

	void update() override
	{
		m_currentCount = m_currentCount - 1;

		if (m_currentCount > 0)
		{
			return;
		}

		m_manager->popScene();
	}

	void draw(Renderer& renderer) override
	{
		int alpha = (int)(m_currentCount / m_fadeCount * 255);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		renderer.drawTexture("curtain", 0, 0, 0, 0, 100, 100, 0.0f);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	void cleanUp() override
	{

	}

	bool isSwallow() const override
	{
		return m_isSwallow;
	}

private:

	const float m_fadeCount;

	float m_currentCount;

	const bool m_isSwallow;
};
