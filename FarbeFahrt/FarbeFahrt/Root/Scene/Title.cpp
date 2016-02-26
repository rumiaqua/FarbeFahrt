# include "Title.h"

# include "Utility/Loader.h"
# include "Utility/Input.h"
# include "Utility/Mouse.h"
# include "Utility/Renderer.h"
# include "Utility/BGM.h"
#include "Utility/Def.h"
#include "Utility/Debug.h"
#include "Utility/HandleList.h"
#include "Utility/SingletonFinalizer.h"
#include "Utility/Math.h"
#include "Utility/Easing.h"

# include "ISceneMediator.h"
# include "Scene.h"

#include "Utility/SE.h"

namespace
{
	const float Scale = 1.0f;
	const float MaxAlpha = 255.0f / 5;
}

Title::Title()
	: m_selectFinish()
	, m_selectStart()
	, m_alpha()
	, m_alphaSwitch()
	, m_transRate()
	, m_timer(0)
{

}

void Title::loadContents(Loader& loader)
{
	loader.loadContent("Title", "Texture/title.png");
	loader.loadContent("TitleBigBackGround", "Texture/titleBigBackGround.png");
	loader.loadContent("TitleBigOther", "Texture/titleBigOther.png");
	loader.loadContent("TitleBigIvy", "Texture/titleBigIvy.png");
	loader.loadContent("TitleBigBubble", "Texture/titleBigBubble.png");
	loader.loadContent("TitleBigBubble2", "Texture/titleBigBubble2.png");
	loader.loadContent("TitleBGM", "Sound/BGM/Title.mp3");


	loader.loadContent("StartOutMouse", "Texture/TitleUI/start.png");
	loader.loadContent("StartOnMouse", "Texture/TitleUI/start2.png");
	loader.loadContent("EndOutMouse", "Texture/TitleUI/end.png");
	loader.loadContent("EndOnMouse", "Texture/TitleUI/end2.png");
}

void Title::initialize()
{
	GetWindowSize(&m_windowSize.x, &m_windowSize.y);
	m_alpha = 0.0f;
	m_transRate = 1.0f;
	m_alphaSwitch = false;
	m_selectStart = false;
	m_selectFinish = false;
}

void Title::update()
{
	++m_timer;
	if (m_timer >= 1000)
	{
		m_timer = 0;
		m_manager->changeScene(Scene::Prologue, 60.0f);
	}
	BGM::play("TitleBGM");

	m_alpha += m_transRate;
	if (!Math::IsContains(m_alpha, 0.0f, MaxAlpha))
	{
		m_transRate *= -1;
	}

	if (m_alpha < 0.0f)
	{
		m_alphaSwitch = !m_alphaSwitch;
	}

	m_alpha = (float)Math::Clamp(m_alpha, 0.0f, MaxAlpha);

	if (isClickedStart())
	{
		m_selectStart = true;
		m_manager->changeScene(Scene::Opening, 30.0f);
	}
	if (isClickedFinish())
	{
		m_selectFinish = true;
		m_manager->popScene(30.0f);
	}
}

void Title::draw(Renderer& renderer)
{
	float t = Utility::Easing::EaseLinear::InOut(m_alpha / MaxAlpha);

	if (System::GetWindowWidth() >= 1024)
	{
		renderer.drawTexture("TitleBigBackGround", Renderer::AspectType::LetterBox);
		renderer.drawTexture(m_alphaSwitch ? "TitleBigBubble" : "TitleBigBubble2", Renderer::AspectType::LetterBox,
			static_cast<int>(t * 255.0f));
		renderer.drawTexture("TitleBigIvy", Renderer::AspectType::LetterBox);
		renderer.drawTexture("TitleBigOther", Renderer::AspectType::LetterBox);
	}
	else
	{
		renderer.drawTexture("Title", Renderer::AspectType::LetterBox);
	}
	//renderer.drawTexture(System::GetWindowWidth() <= 1024 ? "Title" : "TitleBig", Renderer::AspectType::LetterBox);

	renderer.drawTexture(
		inAreaStart() || m_selectStart ? "StartOnMouse" : "StartOutMouse",
		(int)getStartButtonPosition().x, (int)getStartButtonPosition().y, 0, 0, Scale, Scale, 0.0f);

	renderer.drawTexture(
		inAreaFinish() || m_selectFinish ? "EndOnMouse" : "EndOutMouse",
		(int)getFinishButtonPosition().x, (int)getFinishButtonPosition().y, 0, 0, Scale, Scale, 0.0f);
}

void Title::post()
{

}

void Title::cleanUp()
{

}

bool Title::isSwallow() const
{
	return true;
}

bool Title::inAreaStart() const
{
	// 画像サイズ
	int x, y;

	int handle = Singleton<HandleList>::Instance().getHandle("StartOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);

	// マウス座標
	Vector2 mousePosition{ Mouse::Position() };

	// 画像位置
	Vector2 pos{ getStartButtonPosition() };

	return
		Math::IsContains(mousePosition.x, pos.x, pos.x + x * Scale) &&
		Math::IsContains(mousePosition.y, pos.y, pos.y + y * Scale) &&
		!m_selectFinish;
}

bool Title::inAreaFinish() const
{
	// 画像サイズ
	int x, y;
	int handle = Singleton<HandleList>::Instance().getHandle("EndOutMouse");
	DxLib::GetGraphSize(handle, &x, &y);

	// マウス座標
	Vector2 mousePosition{ Mouse::Position() };

	// 画像位置
	Vector2 pos{ getFinishButtonPosition() };

	return
		Math::IsContains(mousePosition.x, pos.x, pos.x + x * Scale) &&
		Math::IsContains(mousePosition.y, pos.y, pos.y + y * Scale) &&
		!m_selectStart;
}

bool Title::isClickedStart() const
{
	return
		Mouse::IsClicked(MOUSE_INPUT_1) &&
		inAreaStart();
}

bool Title::isClickedFinish() const
{
	return
		Mouse::IsClicked(MOUSE_INPUT_1) &&
		inAreaFinish();
}

Vector2 Title::getStartButtonPosition() const
{
	return{ m_windowSize.x * 0.2f, m_windowSize.y * 0.4f };
}

Vector2 Title::getFinishButtonPosition() const
{
	return{ m_windowSize.x * 0.2f, m_windowSize.y * 0.55f };
}
