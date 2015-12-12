# include "Message.h"

# include "Utility/Renderer.h"
# include "Utility/String.h"
# include "Utility/Input.h"
# include "Utility/Debug.h"

# include "GameMain.h"
# include "ISceneMediator.h"

# include "Manager/MessageManager.h"

# include "Message/MessageOperation.h"

# include <numeric>

Message::Message()
	: m_message()
	, m_textStack()
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

	m_message = &MessageManager::Get();
	MessageManager::SetShow(false);

	m_textStack.clear();

	Debug::SetEnabled(true);
	Debug::SetClear(true);
}

void Message::update()
{
	// ���b�Z�[�W�f�[�^�̏���
	processMessage();

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

		if (m_message->empty())
		{
			m_manager->popScene();
		}
	}
}

void Message::draw(Renderer& renderer)
{
	int remain = m_elapsedTime / m_characterPerFrame;

	int numMessage = m_textStack.size();

	int startHeight = 300;

	int fontSize = 32 + 6;

	Debug::Println(String::Create("remain : ", remain));
	Debug::Println(String::Create("elapsedTime : ", m_elapsedTime));

	for (auto it = m_textStack.begin(); it != m_textStack.end(); ++it)
	{
		std::wstring wide = String::ToWide(*it);
		int length = wide.length();
		auto index = it - m_textStack.begin();

		int y = startHeight + fontSize * index;

		// �`��\�c�蕶�����̕������Ȃ���ΐ؂��肵�ĕ`��
		if (remain < length)
		{
			renderer.drawFont(*it, remain, 0, WidthPlacement::Center, y, HeightPlacement::Top);
			break;
		}

		// �`��\�c�蕶���������c�蕶�����̕������Ȃ���΍Ō�܂ŕ`��
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
	for (auto&& text : m_textStack)
	{
		length += String::ToWide(text).length();
	}
	return length;
}

void Message::processMessage()
{
	while (!m_message->empty())
	{
		auto&& op = m_message->pop();
		// �e�L�X�g�ǉ�
		if (op.operation == "t")
		{
			m_textStack.push_back(op.message);
		}

		// �摜�\���@������
		if (op.operation == "g")
		{

		}

		// ��x�~�߂�@������
		if (op.operation == "s")
		{

		}
	}
}
