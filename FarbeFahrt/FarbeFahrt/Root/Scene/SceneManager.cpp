# include "SceneManager.h"


SceneManager::SceneManager()
{

}

void SceneManager::update()
{
	m_scenes.at(m_stack.back())->update();
}

void SceneManager::draw(Renderer& renderer) const
{
	for (auto&& key : m_stack)
	{
		m_scenes.at(key)->draw(renderer);
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

void SceneManager::changeScene(const Scene& scene)
{
	m_ops.emplace_back([&] (Loader& loader)
	{
		for (auto&& scene : m_stack)
		{
			m_scenes.at(scene)->cleanUp();
		}
		m_stack.clear();
		m_stack.push_back(scene);
		m_scenes.at(scene)->initialize();
		m_scenes.at(scene)->loadContents(loader);
	});
}

void SceneManager::replaceScene(const Scene& scene)
{
	m_ops.emplace_back([=] (Loader& loader)
	{
		m_scenes.at(m_stack.back())->cleanUp();
		m_stack.pop_back();
		m_stack.push_back(scene);
		m_scenes.at(scene)->initialize();
		m_scenes.at(scene)->loadContents(loader);
	});
}

void SceneManager::pushScene(const Scene& scene)
{
	m_ops.emplace_back([=] (Loader& loader)
	{
		m_stack.push_back(scene);
		m_scenes.at(scene)->initialize();
		m_scenes.at(scene)->loadContents(loader);
	});
}

void SceneManager::popScene()
{
	m_ops.emplace_back([=] (Loader&)
	{
		m_scenes.at(m_stack.back())->cleanUp();
		m_stack.pop_back();
	});
}
