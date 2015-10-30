# include "SceneManager.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/MemoryCast.h"

SceneManager::SceneManager()
{

}

void SceneManager::update()
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
	{
		(*it)->update();
		if ((*it)->isSwallow())
		{
			return;
		}
	}
}

void SceneManager::draw(Renderer& renderer) const
{
	for (auto&& scene : m_stack)
	{
		scene->draw(renderer);
	}
}

void SceneManager::resolve(Loader& loader)
{
	for (auto&& op : m_ops)
	{
		op(loader);
	}
	m_ops.clear();
}

bool SceneManager::hasChanged() const
{
	return !m_ops.empty();
}

void SceneManager::changeScene(const Scene& scene, float t, bool isSwallow)
{
	pushOperation([=] (Loader& loader)
	{
		push(std::make_shared<FadeOut>(
			t, [=] { changeScene(scene); }, isSwallow), loader);
	});
}

void SceneManager::replaceScene(const Scene& scene, float t, bool isSwallow)
{
	pushOperation([=] (Loader& loader)
	{
		push(std::make_shared<FadeOut>(
			t, [=] { replaceScene(scene); }, isSwallow), loader);
	});
}

void SceneManager::pushScene(const Scene& scene, float t, bool isSwallow)
{
	pushOperation([=] (Loader& loader)
	{
		push(std::make_shared<FadeOut>(
			t, [=] { pushScene(scene); }, isSwallow), loader);
	});
}

void SceneManager::popScene(float t, bool isSwallow)
{
	pushOperation([=] (Loader& loader)
	{
		push(std::make_shared<FadeOut>(
			t ,[=] { popScene(); }, isSwallow), loader);
	});
}

void SceneManager::changeScene(const Scene& scene)
{
	pushOperation([=] (Loader& loader)
	{
		clear();
		push(m_scenes.at(scene), loader);
	});
}

void SceneManager::replaceScene(const Scene& scene)
{
	pushOperation([=] (Loader& loader)
	{
		pop();
		push(m_scenes.at(scene), loader);
	});
}

void SceneManager::pushScene(const Scene& scene)
{
	pushOperation([=] (Loader& loader)
	{
		push(m_scenes.at(scene), loader);
	});
}

void SceneManager::popScene()
{
	pushOperation([=] (Loader&)
	{
		pop();
	});
}

void SceneManager::push(const ScenePtr& scene, Loader& loader)
{
	m_stack.push_back(scene);
	scene->setManagerPtr(this);
	scene->initialize();
	scene->loadContents(loader);
}

void SceneManager::pop()
{
	m_stack.back()->cleanUp();
	m_stack.pop_back();
}

void SceneManager::clear()
{
	for (size_t i = 0; i < m_stack.size(); ++i)
	{
		pop();
	}
}

void SceneManager::pushOperation(const Operation& operation)
{
	m_ops.emplace_back(operation);
}

// -----------------------------------------------------------
// FadeIn
// -----------------------------------------------------------

SceneManager::FadeIn::FadeIn(float fadeCount, bool isSwallow)
	: m_fadeCount(fadeCount)
	, m_currentCount(fadeCount)
	, m_isSwallow(isSwallow)
{

}

void SceneManager::FadeIn::loadContents(Loader& loader)
{
	loader.loadContent("curtain", "Texture/curtain.png");
}

void SceneManager::FadeIn::initialize()
{

}

void SceneManager::FadeIn::update()
{
	m_currentCount = m_currentCount - 1;

	if (m_currentCount > 0)
	{
		return;
	}

	m_manager->popScene();
}

void SceneManager::FadeIn::draw(Renderer& renderer)
{
	int alpha = (int)(m_currentCount / m_fadeCount * 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	renderer.drawTexture("curtain", 0, 0, 0, 0, 100, 100, 0.0f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneManager::FadeIn::cleanUp()
{

}

bool SceneManager::FadeIn::isSwallow() const
{
	return m_isSwallow;
}

// -----------------------------------------------------------
// FadeOut
// -----------------------------------------------------------

SceneManager::FadeOut::FadeOut(float fadeCount, const std::function<void()>& operation, bool isSwallow)
	: m_fadeCount(fadeCount)
	, m_currentCount(fadeCount)
	, m_operation(operation)
	, m_isSwallow(isSwallow)
{

}

void SceneManager::FadeOut::loadContents(Loader& loader)
{
	loader.loadContent("curtain", "Texture/curtain.png");
}

void SceneManager::FadeOut::initialize()
{

}

void SceneManager::FadeOut::update()
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
		manager->push(std::make_shared<FadeIn>(count, isSwallow), loader);
	});
}

void SceneManager::FadeOut::draw(Renderer& renderer)
{
	int alpha = (int)(m_currentCount / m_fadeCount * 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
	renderer.drawTexture("curtain", 0, 0, 0, 0, 100, 100, 0.0f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneManager::FadeOut::cleanUp()
{

}

bool SceneManager::FadeOut::isSwallow() const
{
	return m_isSwallow;
}
