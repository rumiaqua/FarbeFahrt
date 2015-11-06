# pragma once

# include <deque>

/// <summary>�������g�p�^�[��</summary>
/// <summary>�^�ɑ΂��f�t�H���g�R���X�g���N�^��v�����܂�</summary>
template <typename Type>
class Memento
{
private:

	using Buffer = std::deque<Type>;

	using Size = typename Buffer::size_type;

public:

	/// <summary>�R���X�g���N�^</summary>
	/// <param name="bufferSize">�o�b�t�@�̃T�C�Y</param>
	/// <param name="isFill">�o�b�t�@�𖄂߂邩�ǂ���</param>
	Memento(const Size& bufferSize, bool isFill = true)
		: m_buffer()
		, m_bufferSize(bufferSize + 1)
		, m_isFill(isFill)
	{
		tryFill(true);
	}

public:

	/// <summary>�o�b�t�@�̃T�C�Y��ύX����</summary>
	void changeBufferSize(const Size& bufferSize)
	{
		m_bufferSize = bufferSize + 1;
		resolve();
		tryFill(false);
	}

	/// <summary>�l��ۑ�����</summary>
	const Type& save(const Type& value)
	{
		return save(value, true);
	}

	/// <summary>�l������ō\�z���ĕۑ�����</summary>
	template <typename ...Args>
	void emplace(Args&& ...args)
	{
		m_buffer.emplace_back(std::forward<Args>(args)...);
		resolve();
	}

	/// <summary>������H��</summary>
	const Type& history(const Size& numPrevious)
	{
		// ����ۑ�����Ă��Ȃ��ꍇ�A�G���[
		if (count() == 0)
		{
			throw std::out_of_range("�������ۑ�����Ă��܂���");
		}

		// �ۑ�����葽���k�낤�Ƃ����ꍇ�A�ł��Â��f�[�^��Ԃ�
		Size index = count() > numPrevious ? count() - numPrevious : count();
		index -= 1;
		Buffer::iterator it = m_buffer.begin();
		for (Size i = 0; i < index; ++i)
		{
			++it;
		}
		return *it;
	}

	/// <summary>�������畜������</summary>
	const Type& restore(const Size& numPrevious)
	{
		Size index = count() > numPrevious ? numPrevious : 0;
		for (Size i = 0; i < index; ++i)
		{
			m_buffer.pop_back();
		}
		tryFill(false);
		return at(index);
	}

private:

	/// <summary>�l��ۑ�����</summary>
	/// <param name="isPost">�����ɒǉ����邩�ǂ���</param>
	const Type& save(const Type& value, bool isPost)
	{
		isPost ? m_buffer.push_back(value) : m_buffer.push_front(value);
		resolve();
		return m_buffer.back();
	}

	/// <summary>�I�[�o�[�t���[����������</summary>
	void resolve()
	{
		if (count() < capacity())
		{
			return;
		}
		for (Size i = 0; i < count() - capacity(); ++i)
		{
			m_buffer.pop_front();
		}
	}

	/// <summary>�o�b�t�@�ɕۑ�����Ă���l�̐���Ԃ�</summary>
	Size count() const
	{
		return m_buffer.size();
	}

	/// <summary>���e����Ă���T�C�Y��Ԃ�</summary>
	Size capacity() const
	{
		return m_bufferSize - 1;
	}

	/// <summary>�l�Ŗ��߂�</summary>
	/// <param name="isPost">�����ɒǉ����邩�ǂ���</param>
	void fill(bool isPost)
	{
		Size loop = capacity() - count();
		for (Size i = 0; i < loop; ++i)
		{
			save(Type(), isPost);
		}
	}

	/// <summary>�l�Ŗ��߂邩���s����</summary>
	void tryFill(bool isPost)
	{
		if (m_isFill)
		{
			fill(isPost);
		}
	}

	/// <summary>�w�肵���C���f�b�N�X�̒l��Ԃ�</summary>
	const Type& at(const Size& index) const
	{
		Buffer::const_iterator it = m_buffer.begin();
		for (Size i = 0; i < index; ++i)
		{
			++it;
		}
		return *it;
	}

private:

	Buffer m_buffer;

	Size m_bufferSize;

	bool m_isFill;
};
