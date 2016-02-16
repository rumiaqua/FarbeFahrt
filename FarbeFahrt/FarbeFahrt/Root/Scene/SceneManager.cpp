# include "SceneManager.h"

# include "Frame/BaseScene.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/MemoryCast.h"

# include "FadeIn.inl"
# include "FadeOut.inl"

SceneManager::SceneManager()
	: m_nowStaffRoll(false)
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

void SceneManager::post() const
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
	{
		(*it)->post();
		if ((*it)->isSwallow())
		{
			return;
		}
	}
}

bool SceneManager::hasChanged() const
{
	return !m_ops.empty();
}

void SceneManager::setNowStaffRoll(bool staffRoll)
{
	m_nowStaffRoll = staffRoll;
}

bool SceneManager::isNowStaffRoll()
{
	return m_nowStaffRoll;
}

void SceneManager::changeScene(const Scene& scene, float t, bool isSwallow)
{
	pushOperation([=](Loader& loader)
	{
		push(create<FadeOut>(
			t, [=] { changeScene(scene); }, isSwallow), loader);
	});
}

void SceneManager::replaceScene(const Scene& scene, float t, bool isSwallow)
{
	pushOperation([=](Loader& loader)
	{
		push(create<FadeOut>(
			t, [=] { replaceScene(scene); }, isSwallow), loader);
	});
}

void SceneManager::pushScene(const Scene& scene, float t, bool isSwallow)
{
	pushOperation([=](Loader& loader)
	{
		push(create<FadeOut>(
			t, [=] { pushScene(scene); }, isSwallow), loader);
	});
}

void SceneManager::popScene(float t, bool isSwallow)
{
	pushOperation([=](Loader& loader)
	{
		push(create<FadeOut>(
			t, [=] { popScene(); }, isSwallow), loader);
	});
}

void SceneManager::changeScene(const Scene& scene)
{
	pushOperation([=](Loader& loader)
	{
		clear();
		push(m_scenes.at(scene), loader);
	});
}

void SceneManager::replaceScene(const Scene& scene)
{
	pushOperation([=](Loader& loader)
	{
		pop();
		push(m_scenes.at(scene), loader);
	});
}

void SceneManager::pushScene(const Scene& scene)
{
	pushOperation([=](Loader& loader)
	{
		push(m_scenes.at(scene), loader);
	});
}

void SceneManager::popScene()
{
	pushOperation([=](Loader&)
	{
		pop();
	});
}

void SceneManager::push(const ScenePtr& scene, Loader& loader)
{
	m_stack.push_back(scene);
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
	size_t size = m_stack.size();
	for (size_t i = 0; i < size; ++i)
	{
		pop();
	}
}

void SceneManager::pushOperation(const Operation& operation)
{
	m_ops.emplace_back(operation);
}
