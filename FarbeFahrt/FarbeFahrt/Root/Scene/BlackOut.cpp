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
}

void BlackOut::update()
{
	//ここに暗転中の処理を書く予定だよ
}

void BlackOut::draw(Renderer& renderer)
{
	m_renderer = renderer;
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
