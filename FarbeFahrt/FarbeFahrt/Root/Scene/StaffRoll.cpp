# include "StaffRoll.h"

# include "ISceneMediator.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/Mouse.h"

# include "Utility/HandleList.h"
# include "Utility/SingletonFinalizer.h"

# include "Utility/Point2.h"

# include "Scene.h"
# include "Utility\BGM.h"
StaffRoll::StaffRoll()
	: m_elapsedTime(0.0f)
	, m_needTime(30.0f * 60.0f)
{

}

void StaffRoll::loadContents(Loader& loader)
{
	loader.loadContent("staffRoll", "Texture/StaffRoll.png");
}

void StaffRoll::initialize()
{
	m_elapsedTime = 0.0f;
	m_manager->setNowStaffRoll(true);
}

void StaffRoll::update()
{
	if (m_elapsedTime > m_needTime ||
		Mouse::IsClicked(MOUSE_INPUT_2))
	{
		m_manager->setNowStaffRoll(false);
		m_manager->changeScene(Scene::Title, 180.0f);
	}

	if (Mouse::IsPressed(MOUSE_INPUT_1))
	{
		m_elapsedTime += 9.0f;
	}

	m_elapsedTime += 1.0f;
}

void StaffRoll::draw(Renderer& renderer)
{
	SetBackgroundColor(32, 32, 32);
	Vector2 currectionSize = renderer.getCorrectionSize("staffRoll", Renderer::AspectType::Expand);

	float t = m_elapsedTime / m_needTime;

	renderer.drawTexture("staffRoll", Renderer::AspectType::Expand, Vector2(0.0f, -currectionSize.y * t), Vector2::Zero());
}

void StaffRoll::post()
{
	
}

void StaffRoll::cleanUp()
{
}

bool StaffRoll::isSwallow() const
{
	return true;
}
