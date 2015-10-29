# pragma once

# include <string>

class String
{
public:

	/// <summary>デフォルトコンストラクタ</summary>
	String();

	/// <summary>マルチバイト文字列で初期化</summary>
	/// <param name="str">マルチバイト文字列</param>
	String(const char* str);

	/// <summary>ワイド文字列で初期化</summary>
	/// <param name="str">ワイド文字列</param>
	String(const wchar_t* str);

	/// <summary>stringクラスで初期化</summary>
	/// <param name="str">stringクラス</param>
	String(const std::string& str);

	/// <summary>wstringクラスで初期化</summary>
	/// <param name="str">wstringクラス</param>
	String(const std::wstring& str);

public:

	/// <summary>代入演算子</summary>
	/// <param name="str">文字列</param>
	String& operator = (const String& str);

	/// <summary>指定したインデックスの文字を返す</summary>
	/// <param name="index">インデックス</param>
	wchar_t operator [] (unsigned int index) const;

public:

	/// <summary>文字列の長さを返す</summary>
	unsigned int length() const;

	/// <summary>ワイド文字列を返す</summary>
	std::wstring toWide() const;

	/// <summary>マルチバイト文字列を返す</summary>
	std::string toNarrow() const;

public:

	/// <summary>文字列の長さを返す</summary>
	/// <param name="str">文字列</param>
	static unsigned int length(const String& str);

	/// <summary>ワイド文字列に変換する</summary>
	/// <param name="narrow">マルチバイト文字列</param>
	static std::wstring toWide(const std::string& narrow);

	/// <summary>マルチバイト文字列に変換する</summary>
	/// <param name="wide">ワイド文字列</param>
	static std::string toNarrow(const std::wstring& wide);

	/// <summary>マルチバイト文字列を返す</summary>
	/// <param name="str">文字列</param>
	static std::string toNarrow(const String& str);

	/// <summary>ワイド文字列を返す</summary>
	/// <param name="str">文字列</param>
	static std::wstring toWide(const String& str);

	static String create(const String& value);

	static String create(const char* value);

	static String create(const wchar_t* value);

	static String create(const std::string& value);

	static String create(const std::wstring& value);

	static String create(long double value);

	static String create(double value);

	static String create(float value);

	static String create(unsigned long long value);

	static String create(long long value);

	static String create(unsigned long value);

	static String create(long value);

	static String create(unsigned int value);

	static String create(int value);

	template <typename Type, typename ...Args>
	static String create(const Type& value, Args&& ...args)
	{
		return create(value) + create(std::forward<Args>(args)...);
	}

public:

	bool operator == (const String& str) const;

	bool operator != (const String& str) const;

	String& operator += (const String& str);

	String operator + (const String& str) const;

private:

	/// <summary>wstringクラス</summary>
	std::wstring m_str;
};

namespace std
{
	template <>
	struct hash<String>
	{
		inline std::size_t operator() (const String& key) const
		{
			return std::hash<std::string>()(key.toNarrow());
		}
	};
}

std::ostream& operator << (std::ostream& stream, const String& str);
