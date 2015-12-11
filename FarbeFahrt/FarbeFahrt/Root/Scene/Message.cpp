# include "Message.h"

# include "Utility/Renderer.h"
# include "Utility/String.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "Scene/GameMain.h"

# include "Manager/MessageManager.h"

# include <numeric>

Message::Message()
	: m_message()
	, m_elapsedTime(0.0f)
	, m_characterPerFrame(1.0f)
{
	
}

void Message::loadContents(Loader& loader)
{

}

void Message::initialize()
{
	m_elapsedTime = 0.0f;

	m_message = MessageManager::Get();
	MessageManager::Clear();
	MessageManager::SetShow(false);

	Debug::SetEnabled(true);
	Debug::SetClear(true);
}

void Message::update()
{
	++m_elapsedTime;
	float totalTime = getLengthMessage() * m_characterPerFrame;
	if (m_elapsedTime > totalTime)
	{
		m_elapsedTime = totalTime;
	}

	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		if (m_elapsedTime < totalTime)
		{
			m_elapsedTime = totalTime;
			return;
		}
		m_manager->popScene();
	}
}

void Message::draw(Renderer& renderer)
{
	int remain = m_elapsedTime / m_characterPerFrame;

	int numMessage = m_message.size();

	int startHeight = 300;

	int fontSize = 32 + 6;

	Debug::Println(String::Create("remain : ", remain));
	Debug::Println(String::Create("elapsedTime : ", m_elapsedTime));

	for (auto it = m_message.begin(); it != m_message.end(); ++it)
	{
		std::wstring wide = String::ToWide(*it);
		int length = wide.length();
		auto index = it - m_message.begin();

		int y = startHeight + fontSize * index;

		// •`‰æ‰Â”\c‚è•¶š”‚Ì•û‚ª­‚È‚¯‚ê‚ÎØ‚èæ‚è‚µ‚Ä•`‰æ
		if (remain < length)
		{
			renderer.drawFont(*it, remain, 0, WidthPlacement::Center, y, HeightPlacement::Top);
			break;
		}

		// •`‰æ‰Â”\c‚è•¶š”‚æ‚è‚àc‚è•¶š”‚Ì•û‚ª­‚È‚¯‚ê‚ÎÅŒã‚Ü‚Å•`‰æ
		if (remain >= length)
		{
			renderer.drawFont(*it, length, 0, WidthPlacement::Center, y, HeightPlacement::Top);
			remain -= length;
		}
	}
}

void Message::post()
{

}

void Message::cleanUp()
{

}

bool Message::isSwallow() const
{
	return true;
}

unsigned int Message::getLengthMessage() const
{
	int length = 0;
	for (auto&& message : m_message)
	{
		length += String::ToWide(message).length();
	}
	return length;
}
