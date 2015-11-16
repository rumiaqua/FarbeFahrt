/// <summary>フェードアウト専用シーン</summary>
class FadeOut final : public BaseScene
{
public:

	FadeOut(float fadeCount, const std::function<void()>& operation, bool isSwallow = false)
		: m_fadeCount(fadeCount)
		, m_currentCount(fadeCount)
		, m_operation(operation)
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
		m_operation();
		// ダウンキャストしてプライベート関数に触る
		SceneManager* manager = dynamic_cast<SceneManager*>(m_manager);
		// VS2013にはジェネリックキャプチャがないので応急処置
		auto& count = m_fadeCount;
		auto& isSwallow = m_isSwallow;
		manager->pushOperation([=] (Loader& loader)
		{
			manager->push(manager->create<FadeIn>(count, isSwallow), loader);
		});
	}

	virtual void draw(Renderer& renderer) override
	{
		int alpha = (int)(m_currentCount / m_fadeCount * 255);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
		renderer.drawTexture("curtain", 0, 0, 0, 0, 100, 100, 0.0f);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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

	const std::function<void()> m_operation;

	const bool m_isSwallow;
};
