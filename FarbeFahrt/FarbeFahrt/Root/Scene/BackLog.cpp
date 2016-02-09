# include "BackLog.h"
# include "ISceneMediator.h"
# include "Manager/BackLogManager.h"
# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/Mouse.h"
# include "Utility/Math.h"

BackLog::BackLog()
{
	
}

BackLog::~BackLog()
{

}

void BackLog::loadContents(Loader& loader)
{
	loader.loadContent("curtain", "Texture/curtain.png");
}

void BackLog::initialize()
{
	m_currentRow = BackLogManager::Size();
}

void BackLog::update()
{
	int wheel = Mouse::ScrollValue();
	if (wheel < 0)
	{
		m_currentRow += 1;
	}
	if (wheel > 0)
	{
		m_currentRow -= 1;
	}
	if (Mouse::IsClicked(MOUSE_INPUT_RIGHT))
	{
		m_manager->popScene();
	}
}

void BackLog::draw(Renderer& renderer)
{
	renderer.drawTexture("curtain", 0.1f, 0.05f, 144);

	int size = BackLogManager::Size();

	Point2 textureSize = renderer.getTextureSize("curtain");
	Point2 windowSize = renderer.getWindowSize();
	Vector2 margin { 0.1f, 0.05f };

	Vector2 outside = Vector2(windowSize) * margin;
	Vector2 inside = Vector2(windowSize) - outside * 2;

	int drawable = Math::Min({ (int)Math::Floor(inside.y / 48), BackLogManager::Size() });

	m_currentRow = Math::Max({ 0, Math::Min({ m_currentRow, BackLogManager::Size() - drawable }) });

	Vector2 padding { 0.0f, 0.025f };

	for (int i = 0; i < drawable; ++i)
	{
		renderer.drawFontCenter(BackLogManager::GetRow(i + m_currentRow), outside.y + padding.y * inside.y + i * 48);
	}
}

void BackLog::post()
{

}

void BackLog::cleanUp()
{

}

bool BackLog::isSwallow() const
{
	return true;
}
