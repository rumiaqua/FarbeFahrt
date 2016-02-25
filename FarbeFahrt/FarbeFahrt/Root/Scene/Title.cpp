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

namespace
{
	const float Scale = 1.0f;
	const float MaxAlpha = 255.0f / 5;
}

Title::Title()
{

}

void Title::loadContents(Loader& loader)
{
	loader.loadContent("Title", "Texture/title.png");
	loader.loadContent("TitleBigBackGround", "Texture/titleBigBackGround.png");
	loader.loadContent("TitleBigOther", "Texture/titleBigOther.png");
	loader.loadContent("TitleBigIvy", "Texture/titleBigIvy.png");
	loader.loadContent("TitleBigBubble", "Texture/titleBigBubble.png");
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
}

void Title::update()
{
	BGM::play("TitleBGM");

	m_alpha += m_transRate;
	if (!Math::IsContains(m_alpha, 0.0f, MaxAlpha))
	{
		m_alpha = Math::Clamp(m_alpha, 0.0f, MaxAlpha);
		m_transRate *= -1;
	}

	if (isClickedStart())
	{
		m_manager->changeScene(Scene::Opening, 30.0f);
	}
	if (isClickedFinish())
	{
		m_manager->popScene(30.0f);
	}
}

void Title::draw(Renderer& renderer)
{
	float t = Utility::Easing::EaseCirc::InOut(m_alpha / MaxAlpha);
	t = m_alpha / MaxAlpha;

	if (System::GetWindowWidth() >= 1024)
	{
		renderer.drawTexture("TitleBigBackGround", Renderer::AspectType::LetterBox);
		renderer.drawTexture("TitleBigBubble", Renderer::AspectType::LetterBox, t * 255.0f);
		renderer.drawTexture("TitleBigIvy", Renderer::AspectType::LetterBox);
		renderer.drawTexture("TitleBigOther", Renderer::AspectType::LetterBox);
	}
	else
	{
		renderer.drawTexture("Title", Renderer::AspectType::LetterBox);
	}
	//renderer.drawTexture(System::GetWindowWidth() <= 1024 ? "Title" : "TitleBig", Renderer::AspectType::LetterBox);

	renderer.drawTexture(inAreaStart() ? "StartOnMouse" : "StartOutMouse", (int)getStartButtonPosition().x, (int)getStartButtonPosition().y, 0, 0, Scale, Scale, 0.0f);
	renderer.drawTexture(inAreaFinish() ? "EndOnMouse" : "EndOutMouse", (int)getFinishButtonPosition().x, (int)getFinishButtonPosition().y, 0, 0, Scale, Scale, 0.0f);

	Debug::Println(String::Create("Alpha:",m_alpha));
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
		Math::IsContains(mousePosition.y, pos.y, pos.y + y * Scale);
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
		Math::IsContains(mousePosition.y, pos.y, pos.y + y * Scale);
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
	return{ m_windowSize.x * 0.2f, m_windowSize.y * 0.5f };
}

Vector2 Title::getFinishButtonPosition() const
{
	return{ m_windowSize.x * 0.2f, m_windowSize.y * 0.7f };
}
