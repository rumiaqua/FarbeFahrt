# include "Message.h"

# include "Utility/Renderer.h"
# include "Utility/String.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"
# include "Utility/Loader.h"
# include "Utility/Mouse.h"
# include "Utility/Math.h"
# include "Utility/BGM.h"

# include "GameMain.h"
# include "ISceneMediator.h"

# include "Manager/MessageManager.h"
# include "Manager/BackLogManager.h"

# include "Message/MessageOperation.h"

# include <numeric>

Message::Message()
	: m_message()
	, m_textStack()
	, m_elapsedTime(0.0f)
	, m_characterPerFrame(1.0f)
	, m_isStoped(false)
	, m_elapsedFadeTime(0.0f)
	, m_textureFadeFrame(30.0f)
	, m_deltaFade(1.0f)
	, m_isFade(false)
{

}

void Message::loadContents(Loader& loader)
{

}

void Message::initialize()
{
	m_elapsedTime = 0.0f;

	m_textureName = "";

	m_message = &MessageManager::Get();
	MessageManager::SetShow(false);

	m_textStack.clear();
}

void Message::update()
{
	// メッセージデータの処理
	processMessage();

	if (m_isFade)
	{
		m_elapsedFadeTime += m_deltaFade;
		m_isFade = m_elapsedFadeTime < m_textureFadeFrame;
		m_elapsedFadeTime = Math::Min({ m_elapsedFadeTime, m_textureFadeFrame });
		if (m_isFade)
		{
			return;
		}
	}

	++m_elapsedTime;

	float totalTime = getLengthMessage() * m_characterPerFrame;
	if (m_elapsedTime > totalTime)
	{
		m_elapsedTime = totalTime;
	}

	if (/*Input::IsClicked(KEY_INPUT_RETURN) ||*/
		Mouse::IsClicked(MOUSE_INPUT_1))
	{
		if (m_elapsedTime < totalTime)
		{
			m_elapsedTime = totalTime;
			return;
		}

		m_isStoped = false;
		if (!m_message->empty())
		{
			m_elapsedTime = 0.0f;
			m_textStack.clear();
			processMessage();
			return;
		}

		/*if (m_elapsedFadeTime > 0.0f)
		{
			m_deltaFade = -1.0f;
			m_isFade = true;
			return;
		}
		m_elapsedFadeTime = 0.0f;*/

		if (m_elapsedFadeTime > 0.0f)
		{
			m_manager->popScene(30.0f);
			return;
		}

		m_manager->popScene();
	}
}

void Message::draw(Renderer& renderer)
{
	if (!m_textureName.empty())
	{
		int t = (int)(m_elapsedFadeTime / m_textureFadeFrame * 255);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, t);
		renderer.drawTexture(m_textureName, Renderer::AspectType::LetterBox);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, -1);
	}
	renderMessage(renderer);
}

void Message::post()
{

}

void Message::cleanUp()
{
	BackLogManager::Add("");
}

bool Message::isSwallow() const
{
	return true;
}

unsigned int Message::getLengthMessage() const
{
	int length = 0;
	for (auto&& text : m_textStack)
	{
		length += (int)String::ToWide(text).length();
	}
	return length;
}

void Message::processMessage()
{
	while (!m_message->empty() && !m_isStoped)
	{
		auto&& op = m_message->pop();
		// テキスト追加
		if (op.operation == "t")
		{
			m_textStack.push_back(op.message);
			BackLogManager::Add(op.message);
		}

		// 画像表示
		if (op.operation == "g")
		{
			m_elapsedTime = 0;
			m_elapsedFadeTime = 0.0f;
			m_isFade = true;
			m_textureName = op.message;
		}

		// 一度止める
		if (op.operation == "s")
		{
			m_isStoped = true;
			return;
		}

		// BGM再生
		if (op.operation == "bgm")
		{
			BGM::play(op.message);
		}
	}
}

void Message::renderMessage(Renderer& renderer) const
{
	int remain = (int)(m_elapsedTime / m_characterPerFrame);

	int numMessage = (int)m_textStack.size();

	int startHeight = 300;

	int fontSize = 32 + 6;

	/*Debug::Println(String::Create("remain : ", remain));
	Debug::Println(String::Create("elapsedTime : ", m_elapsedTime));*/

	for (auto it = m_textStack.begin(); it != m_textStack.end(); ++it)
	{
		std::wstring wide = String::ToWide(*it);
		int length = (int)wide.length();
		int index = (int)(it - m_textStack.begin());

		int y = startHeight + fontSize * index;

		// 描画可能残り文字数の方が少なければ切り取りして描画
		if (remain < length)
		{
			renderer.drawFont(*it, remain, 0, WidthPlacement::Center, y, HeightPlacement::Top);
			break;
		}

		// 描画可能残り文字数よりも残り文字数の方が少なければ最後まで描画
		if (remain >= length)
		{
			renderer.drawFont(*it, length, 0, WidthPlacement::Center, y, HeightPlacement::Top);
			remain -= length;
		}
	}
}
