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

# include "Utility/Easing.h"

namespace
{
	const float Scale = 0.5f;
	const float FadeSpeed = 30.0f;

	const float DurationTime = 0.5f * 60.0f;
}

TitleChoose::TitleChoose() :
	m_yesFlag(true)
	, m_noFlag(true)
	, m_windowSize(0, 0)
	, m_state(State::FadeIn)
	, m_elapsedTime(0.0f)
	, m_isYesSelected(none)
	, m_yesPosX()
	, m_noPosX()
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

	m_state = State::FadeIn;
	m_elapsedTime = 0.0f;
	m_isYesSelected = none;
}

void TitleChoose::update()
{
	/*
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

	m_elapsedTime += 1.0f;
	float t = (float)Math::Saturate(m_elapsedTime / DurationTime);
	auto ease = Utility::Easing::EaseBack::InOut;
	m_yesPosX = Math::Lerp(-noWidthPos(), yesWidthPos(), ease(t));
	m_noPosX = Math::Lerp(-yesWidthPos(), noWidthPos(), ease(t));
	*/

	switch (m_state)
	{
	case TitleChoose::State::FadeIn:
		fadeIn();
		break;
	case TitleChoose::State::Wait:
		wait();
		break;
	case TitleChoose::State::FadeOut:
		fadeOut();
		break;
	default:
		break;
	}
}

void TitleChoose::draw(Renderer& renderer)
{
	renderer.drawTexture("TitleChooseBack", Renderer::AspectType::LetterBox, 255);
	renderer.drawTexture(inAreaYes() ? "YesOnMouse" : "YesOutMouse", (int)m_yesPosX, (int)textureHeightPos(), 0, 0, Scale, Scale, 0.0f);
	renderer.drawTexture(inAreaNo() ? "NoOnMouse" : "NoOutMouse", (int)m_noPosX, (int)textureHeightPos(), 0, 0, Scale, Scale, 0.0f);
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

bool TitleChoose::inAreaYes() const
{
	// 画像サイズ
	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("YesOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);

	// マウス座標
	Vector2 mousePosition { Mouse::Position() };

	// 画像位置
	Vector2 pos { getYesButtonPosition() };

	return
		Math::IsContains(mousePosition.x, pos.x, pos.x + x * Scale) &&
		Math::IsContains(mousePosition.y, pos.y, pos.y + y * Scale);
}

bool TitleChoose::inAreaNo() const
{
	// 画像サイズ
	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("NoOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);

	// マウス座標
	Vector2 mousePosition { Mouse::Position() };

	// 画像位置
	Vector2 pos { getNoButtonPosition() };

	return
		Math::IsContains(mousePosition.x, pos.x, pos.x + x * Scale) &&
		Math::IsContains(mousePosition.y, pos.y, pos.y + y * Scale);
}

bool TitleChoose::isClickedYes() const
{
	return
		Mouse::IsClicked(MOUSE_INPUT_1) &&
		inAreaYes();
}

bool TitleChoose::isClickedNo() const
{
	return
		Mouse::IsClicked(MOUSE_INPUT_1) &&
		inAreaNo() ||
		Input::IsClicked(KEY_INPUT_ESCAPE);
}

Vector2 TitleChoose::getYesButtonPosition() const
{
	return { m_windowSize.x * 0.32f, m_windowSize.y * 0.5f };
}

Vector2 TitleChoose::getNoButtonPosition() const
{
	return { m_windowSize.x * 0.55f, m_windowSize.y * 0.5f };
}

void TitleChoose::fadeIn()
{
	m_elapsedTime += 1.0f;
	float t = m_elapsedTime / DurationTime;
	if (t >= 1.0f)
	{
		m_state = State::Wait;
	}

	Vector2 yes { getYesButtonPosition() };
	Vector2 no { getNoButtonPosition() };
	t = Utility::Easing::EaseQuad::InOut((float)Math::Saturate(t));
	m_yesPosX = Math::Lerp(-no.x, yes.x, t);
	m_noPosX = Math::Lerp(-yes.x, no.x, t);
}

void TitleChoose::wait()
{
	if (isClickedYes())
	{
		m_elapsedTime = 0.0f;
		m_isYesSelected = true;
		m_state = State::FadeOut;
	}
	if (isClickedNo())
	{
		m_elapsedTime = 0.0f;
		m_isYesSelected = false;
		m_state = State::FadeOut;
	}
}

void TitleChoose::fadeOut()
{
	m_elapsedTime += 1.0f;
	float t = m_elapsedTime / DurationTime;
	Vector2 yes { getYesButtonPosition() };
	Vector2 no { getNoButtonPosition() };
	t = Utility::Easing::EaseQuad::InOut((float)Math::Saturate(t));
	m_yesPosX = Math::Lerp(yes.x, yes.x + m_windowSize.x, t);
	m_noPosX = Math::Lerp(no.x, no.x + m_windowSize.x, t);
	if (t >= 1.0f)
	{
		if (m_isYesSelected.ref())
		{
			m_manager->changeScene(Scene::Title, 30.0f);
		}
		else
		{
			m_manager->popScene();
		}
		BGM::stop();
	}
}
