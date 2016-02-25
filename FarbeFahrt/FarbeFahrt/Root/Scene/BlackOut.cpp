# include "BlackOut.h"

# include "ISceneMediator.h"

BlackOut::BlackOut()
{

}

void BlackOut::loadContents(Loader& loader)
{

}

void BlackOut::initialize()
{
	m_once = true;
}

void BlackOut::update()
{
	if (m_once)
	{
		m_manager->popScene(60.0f, false);
		m_once = false;
	}
}

void BlackOut::draw(Renderer& renderer)
{
	renderer.drawTexture("curtain",Renderer::AspectType::Fit);
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
