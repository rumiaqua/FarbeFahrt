# include "BlackOut.h"

# include "ISceneMediator.h"

# include "Utility/StoryManager/StoryManager.h"

BlackOut::BlackOut()
{

}

void BlackOut::loadContents(Loader& loader)
{

}

void BlackOut::initialize()
{

}

void BlackOut::update()
{
	if (StoryManager::get(BitFlag::ADELE))
	{
		StoryManager::set(BitFlag::RIDEON);
	}
	m_manager->popScene(60.0f, true);
}

void BlackOut::draw(Renderer& renderer)
{
	renderer.drawTexture("curtain", Renderer::AspectType::Fit);
	renderer.ChangeNight();
}

void BlackOut::post()
{

}

void BlackOut::cleanUp()
{

}

bool BlackOut::isSwallow() const
{
	return true;
}
