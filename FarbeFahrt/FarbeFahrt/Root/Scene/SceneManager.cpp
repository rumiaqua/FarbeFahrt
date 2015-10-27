#include "SceneManager.h"

SceneManager::SceneManager()
{

}

void SceneManager::changeScene(const Scene & scene)
{
	m_ops.emplace_back([&] ()
	{
		m_stack.clear();
		m_stack.push_back(scene);
	});
}

void SceneManager::replaceScene(const Scene & scene)
{
	m_ops.emplace_back([&] ()
	{
		m_stack.pop_back();
		m_stack.push_back(scene);
	});
}

void SceneManager::pushScene(const Scene & scene)
{
	m_ops.emplace_back([&] ()
	{
		m_stack.push_back(scene);
	});
}

void SceneManager::popScene()
{
	m_ops.emplace_back([&] ()
	{
		m_stack.pop_back();
	});
}

void SceneManager::Resolve()
{
	for (auto&& op : m_ops)
	{
		op();
	}
	m_ops.clear();
}
