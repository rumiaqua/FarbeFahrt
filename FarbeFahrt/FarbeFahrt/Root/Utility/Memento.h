# pragma once

# include <deque>

/// <summary>メメントパターン</summary>
/// <summary>型に対しデフォルトコンストラクタを要求します</summary>
template <typename Type>
class Memento
{
private:

	using Buffer = std::deque<Type>;

	using Size = typename Buffer::size_type;

public:

	/// <summary>コンストラクタ</summary>
	/// <param name="bufferSize">バッファのサイズ</param>
	/// <param name="isFill">バッファを埋めるかどうか</param>
	Memento(const Size& bufferSize, bool isFill = true)
		: m_buffer()
		, m_bufferSize(bufferSize + 1)
		, m_isFill(isFill)
	{
		tryFill(true);
	}

public:

	/// <summary>バッファのサイズを変更する</summary>
	void changeBufferSize(const Size& bufferSize)
	{
		m_bufferSize = bufferSize + 1;
		resolve();
		tryFill(false);
	}

	/// <summary>値を保存する</summary>
	const Type& save(const Type& value)
	{
		return save(value, true);
	}

	/// <summary>値を内部で構築して保存する</summary>
	template <typename ...Args>
	void emplace(Args&& ...args)
	{
		m_buffer.emplace_back(std::forward<Args>(args)...);
		resolve();
	}

	/// <summary>履歴を辿る</summary>
	const Type& history(const Size& numPrevious)
	{
		// 一つも保存されていない場合、エラー
		if (count() == 0)
		{
			throw std::out_of_range("履歴が保存されていません");
		}

		// 保存数より多く遡ろうとした場合、最も古いデータを返す
		Size index = count() > numPrevious ? count() - numPrevious : count();
		index -= 1;
		Buffer::iterator it = m_buffer.begin();
		for (Size i = 0; i < index; ++i)
		{
			++it;
		}
		return *it;
	}

	/// <summary>履歴から復元する</summary>
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

	/// <summary>値を保存する</summary>
	/// <param name="isPost">末尾に追加するかどうか</param>
	const Type& save(const Type& value, bool isPost)
	{
		isPost ? m_buffer.push_back(value) : m_buffer.push_front(value);
		resolve();
		return m_buffer.back();
	}

	/// <summary>オーバーフローを解決する</summary>
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

	/// <summary>バッファに保存されている値の数を返す</summary>
	Size count() const
	{
		return m_buffer.size();
	}

	/// <summary>許容されているサイズを返す</summary>
	Size capacity() const
	{
		return m_bufferSize - 1;
	}

	/// <summary>値で埋める</summary>
	/// <param name="isPost">末尾に追加するかどうか</param>
	void fill(bool isPost)
	{
		Size loop = capacity() - count();
		for (Size i = 0; i < loop; ++i)
		{
			save(Type(), isPost);
		}
	}

	/// <summary>値で埋めるか試行する</summary>
	void tryFill(bool isPost)
	{
		if (m_isFill)
		{
			fill(isPost);
		}
	}

	/// <summary>指定したインデックスの値を返す</summary>
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
