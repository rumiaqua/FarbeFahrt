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
	const int TextureHeightPos = 350;
	const int YesWidthPos = 300;
	const int NoWidthPos = 550;
	const float Scale = 0.5f;
	const float FadeSpeed = 30.0f;
}

TitleChoose::TitleChoose() :
	m_yes(true)
	, m_no(true)
	, m_yesPosX(0.0f - NoWidthPos)
	, m_noPosX(0.0f - YesWidthPos)
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
}

void TitleChoose::update()
{
	if (isPop())
	{
		m_manager->popScene();
		BGM::stop();
		m_yesPosX = 0.0f - NoWidthPos;
		m_noPosX = 0.0f - YesWidthPos;
	}
	if (isChange())
	{
		m_manager->changeScene(Scene::Title, 30.0f);
		BGM::stop();
		m_yesPosX = 0.0f - NoWidthPos;
		m_noPosX = 0.0f - YesWidthPos;
	}

	m_yes = isYesRange();
	m_no = isNoRange();

	m_yesPosX += FadeSpeed;
	m_noPosX += FadeSpeed;
	m_yesPosX = (float)Math::Clamp(m_yesPosX, 0.0f - NoWidthPos, YesWidthPos);
	m_noPosX = (float)Math::Clamp(m_noPosX, 0.0f - YesWidthPos, NoWidthPos);
}

void TitleChoose::draw(Renderer& renderer)
{
	renderer.drawTexture("curtain", Renderer::AspectType::LetterBox, 180);
	renderer.drawTexture("TitleChooseBack", Renderer::AspectType::LetterBox, 255);

	renderer.drawTexture(m_yes ? "YesOnMouse" : "YesOutMouse", m_yesPosX, TextureHeightPos, 0, 0, Scale, Scale, 0.0f);

	renderer.drawTexture(m_no ? "NoOnMouse" : "NoOutMouse", m_noPosX, TextureHeightPos, 0, 0, Scale, Scale, 0.0f);

	Debug::Println(String::Create("MousePos:", Point2::ToString(Mouse::Position())));
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
	return Mouse::IsClicked(MOUSE_INPUT_1) && m_no || Input::IsClicked(KEY_INPUT_ESCAPE);
}

bool TitleChoose::isChange()
{
	return Mouse::IsClicked(MOUSE_INPUT_1) && m_yes;
}

bool TitleChoose::isYesRange()
{
	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("YesOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);
	Point2 mousePosition = Mouse::Position();

	return Math::IsContains<float>(mousePosition.x, YesWidthPos, YesWidthPos + x * Scale)
		&& Math::IsContains<float>(mousePosition.y, TextureHeightPos, TextureHeightPos + y * Scale)
		&& m_yesPosX >= YesWidthPos;
}

bool TitleChoose::isNoRange()
{
	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("NoOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);
	Point2 mousePosition = Mouse::Position();

	return Math::IsContains<float>(mousePosition.x, NoWidthPos, NoWidthPos + x * Scale)
		&& Math::IsContains<float>(mousePosition.y, TextureHeightPos, TextureHeightPos + y * Scale)
		&& m_noPosX >= NoWidthPos;
}
