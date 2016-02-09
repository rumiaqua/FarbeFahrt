# include "BackLog.h"
# include "ISceneMediator.h"
# include "Manager/BackLogManager.h"
# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/Mouse.h"

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

}

void BackLog::update()
{
	if (Mouse::IsClicked(MOUSE_INPUT_RIGHT))
	{
		m_manager->popScene();
	}
}

void BackLog::draw(Renderer& renderer)
{
	renderer.drawTexture("curtain", 0.1f, 0.05f, 144);

	int size = BackLogManager::Size();
	for (int i = 0; i < size; ++i)
	{
		renderer.drawFontCenter(BackLogManager::GetRow(i), 64 + i * 48);
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
