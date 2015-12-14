# pragma once

# include <memory>

/// <summary>無効値</summary>
const struct NullOpt
{

} none;

/// <summary>無効値を表現できる値クラス</summary>
template <typename Type>
class Optional
{
public:

	/// <summary>デフォルトコンストラクタ</summary>
	Optional()
		: m_value()
	{

	}

	/// <summary>仮想デストラクタ</summary>
	virtual ~Optional()
	{

	}

	explicit Optional(const Type& value)
		: m_value(std::make_unique<Type>(value))
	{

	}

	explicit Optional(Type&& value)
		: m_value(new Type(value))
	{

	}

	/// <summary>可変長引数コンストラクタ</summary>
	template <typename ...Args>
	explicit Optional(Args&& ...args)
		: m_value(std::make_unique<Type>(std::forward<Args>(args)...))
	{

	}

	/// <param name="nullopt">無効値</param>
	Optional(const NullOpt& nullopt)
		: m_value()
	{

	}

	/// <summary>コピーコンストラクタ</summary>
	Optional(const Optional& other)
		: m_value(other ? std::make_unique<Type>(*other) : nullptr)
	{

	}

	/// <summary>ムーブコンストラクタ</summary>
	Optional(Optional&& other)
		: m_value(other ? other.m_value.release() : nullptr)
	{

	}

	Optional& operator = (const Type& value)
	{
		return *this = Optional(value);
	}

	/// <param name="nullopt">無効値</param>
	Optional& operator = (const NullOpt& nullopt)
	{
		release();
		return *this;
	}

	Optional& operator = (const Optional& other)
	{
		Optional& own = *this;

		if (own && other)
		{
			*own = *other;
		}
		else if (!own && other)
		{
			create(*other);
		}
		else if (own && !other)
		{
			release();
		}

		return *this;
	}

	Optional& operator = (Optional&& other)
	{
		if ((*this) && !other)
		{
			release();
		}
		else if (other)
		{
			create(std::move(*other));
		}
		return *this;
	}

	/// <summary>生成</summary>
	void create(const Type& value)
	{
		release();
		m_value.reset(new Type(value));
	}

	/// <summary>生成</summary>
	void create(Type&& value)
	{
		release();
		m_value.reset(new Type(std::forward<Type>(value)));
	}

	/// <summary>解放</summary>
	void release()
	{
		m_value.reset();
	}

	/// <summary>代入</summary>
	/// <param name="args">引数</param>
	template <typename ...Args>
	void emplace(Args&& ...args)
	{
		m_value = std::make_unique<Type>(std::forward<Args>(args)...);
	}

public:

	operator const bool() const
	{
		return isEnabled();
	}

	Type& operator * ()
	{
		return ref();
	}

	const Type& operator * () const
	{
		return ref();
	}

	Type* operator & ()
	{
		return pointer();
	}

	const Type* operator & () const
	{
		return pointer();
	}

	/// <summary>値が有効かどうかを返す</summary>
	bool isEnabled() const
	{
		return m_value.get() != nullptr;
	}

	/// <summary>参照を返す</summary>
	Type& ref()
	{
		return *m_value.get();
	}

	/// <summary>参照を返す</summary>
	const Type& ref() const
	{
		return *m_value.get();
	}

	/// <summary>ポインタを返す</summary>
	Type* pointer()
	{
		return m_value.get();
	}

	/// <summary>ポインタを返す</summary>
	const Type* pointer() const
	{
		return m_value.get();
	}

private:

	std::unique_ptr<Type> m_value;
};

/// <summary>Optionalを構築する</summary>
/// <param name="args">引数</param>
template <typename Type, typename ...Args>
Optional<Type>&& makeOptional(Args&& ...args)
{
	return std::move(Optional<Type>(std::forward<Args>(args)...));
}

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Optional<Type>& opt)
{
	stream << opt.Ref();
	return stream;
}

template <typename Type>
bool operator != (const Optional<Type>& o1, const Optional<Type>& o2)
{
	return !(o1 == o2);
}

template <typename Type>
bool operator == (const Optional<Type>& o, const NullOpt&)
{
	return !o;
}

template <typename Type>
bool operator != (const Optional<Type>& o, const NullOpt&)
{
	return o;
}

template <typename Type>
bool operator == (const NullOpt&, const Optional<Type>& o)
{
	return !o;
}

template <typename Type>
bool operator != (const NullOpt&, const Optional<Type>& o)
{
	return o;
}

template <typename Type>
bool operator == (const Optional<Type>& o1, const Optional<Type>& o2)
{
	if (o1.isEnabled() != o2.isEnabled())
	{
		return false;
	}
	if (!o1)
	{
		return true;
	}
	return *o1 == *o2;
}
