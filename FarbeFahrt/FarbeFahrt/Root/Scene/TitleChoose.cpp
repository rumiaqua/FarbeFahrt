# include "TitleChoose.h"
# include "ISceneMediator.h"
# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/Mouse.h"
#include "Utility/Input.h"
#include "Utility/HandleList.h"
#include "Utility/SingletonFinalizer.h"

#include "Utility/Debug.h"
#include "Utility/String.h"
#include "Utility/Math.h"
#include "Scene.h"
#include "Utility/BGM.h"

namespace
{
	const float Scale = 0.5f;
	const float FadeSpeed = 30.0f;
}

TitleChoose::TitleChoose() :
	m_yesFlag(true)
	, m_noFlag(true)
	, m_windowSize(0, 0)
{
}

TitleChoose::~TitleChoose()
{

}

void TitleChoose::loadContents(Loader& loader)
{
}

void TitleChoose::initialize()
{
	GetWindowSize(&m_windowSize.x, &m_windowSize.y);
	m_yesPosX = 0 - noWidthPos();
	m_noPosX = 0 - yesWidthPos();
}

void TitleChoose::update()
{
	if (isPop())
	{
		m_manager->popScene();
		BGM::stop();
		m_yesPosX = 0 - noWidthPos();
		m_noPosX = 0 - yesWidthPos();
	}
	if (isChange())
	{
		m_manager->changeScene(Scene::Title, 30.0f);
		BGM::stop();
		m_yesPosX = 0 - noWidthPos();
		m_noPosX = 0 - yesWidthPos();
	}

	m_yesFlag = isYesRange();
	m_noFlag = isNoRange();

	m_yesPosX += FadeSpeed;
	m_noPosX += FadeSpeed;
	m_yesPosX = (float)Math::Clamp(m_yesPosX, 0 - noWidthPos(), yesWidthPos());
	m_noPosX = (float)Math::Clamp(m_noPosX, 0 - yesWidthPos(), noWidthPos());
}

void TitleChoose::draw(Renderer& renderer)
{
	renderer.drawTexture("curtain", 0, 0, 0, 0, (float)m_windowSize.x, (float)m_windowSize.y, 0.0f,180);
	renderer.drawTexture("TitleChooseBack", Renderer::AspectType::LetterBox, 255);

	renderer.drawTexture(m_yesFlag ? "YesOnMouse" : "YesOutMouse", (int)m_yesPosX, (int)textureHeightPos(), 0, 0, Scale, Scale, 0.0f);

	renderer.drawTexture(m_noFlag ? "NoOnMouse" : "NoOutMouse", (int)m_noPosX, (int)textureHeightPos(), 0, 0, Scale, Scale, 0.0f);

	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("YesOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);
	Debug::Println(String::Create("MousePos:", Point2::ToString(Mouse::Position())));
	Debug::Println(String::Create("yesPos:",m_yesPosX));
	Debug::Println(String::Create("yesWidthPos:", yesWidthPos()));
}

void TitleChoose::post()
{

}

void TitleChoose::cleanUp()
{

}

bool TitleChoose::isSwallow() const
{
	return true;
}

bool TitleChoose::isPop()
{
	return Mouse::IsClicked(MOUSE_INPUT_1) && m_noFlag || Input::IsClicked(KEY_INPUT_ESCAPE);
}

bool TitleChoose::isChange()
{
	return Mouse::IsClicked(MOUSE_INPUT_1) && m_yesFlag;
}

bool TitleChoose::isYesRange()
{
	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("YesOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);
	Point2 mousePosition = Mouse::Position();

	return Math::IsContains((float)mousePosition.x, yesWidthPos(), yesWidthPos() + (float)x * Scale)
		&& Math::IsContains((float)mousePosition.y, textureHeightPos(), textureHeightPos() + (float)y * Scale)
		&& (int)m_yesPosX >= (int)yesWidthPos();
}

bool TitleChoose::isNoRange()
{
	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("NoOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);
	Point2 mousePosition = Mouse::Position();

	return Math::IsContains((float)mousePosition.x, noWidthPos(), noWidthPos() + (float)x * Scale)
		&& Math::IsContains((float)mousePosition.y, textureHeightPos(), textureHeightPos() + (float)y * Scale)
		&& (int)m_noPosX >= (int)noWidthPos();
}

float TitleChoose::textureHeightPos()
{
	return m_windowSize.y * 0.5f;
}

float TitleChoose::yesWidthPos()
{
	return m_windowSize.x * 0.32f;
}

float TitleChoose::noWidthPos()
{
	return m_windowSize.x * 0.55f;
}
