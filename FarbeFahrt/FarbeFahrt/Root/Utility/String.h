# pragma once

# include <string>
# include <vector>
# include <sstream>

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
	static unsigned int Length(const String& str);

	/// <summary>ワイド文字列に変換する</summary>
	/// <param name="narrow">マルチバイト文字列</param>
	static std::wstring ToWide(const std::string& narrow);

	/// <summary>マルチバイト文字列に変換する</summary>
	/// <param name="wide">ワイド文字列</param>
	static std::string ToNarrow(const std::wstring& wide);

	/// <summary>マルチバイト文字列を返す</summary>
	/// <param name="str">文字列</param>
	static std::string ToNarrow(const String& str);

	/// <summary>ワイド文字列を返す</summary>
	/// <param name="str">文字列</param>
	static std::wstring ToWide(const String& str);

	static String Create(const String& value);

	static String Create(const char* value);

	static String Create(const wchar_t* value);

	static String Create(const std::string& value);

	static String Create(const std::wstring& value);

	static String Create(long double value);

	static String Create(double value);

	static String Create(float value);

	static String Create(unsigned long long value);

	static String Create(long long value);

	static String Create(unsigned long value);

	static String Create(long value);

	static String Create(unsigned int value);

	static String Create(int value);

	template <typename Type, typename ...Args>
	static String Create(const Type& value, Args&& ...args)
	{
		return Create(value) + Create(std::forward<Args>(args)...);
	}

	static std::vector<String> Split(const String& str, char delim);

	template <typename Type>
	static Type ToValue(const String& str)
	{
		std::stringstream stream(str.toNarrow());
		Type value;
		stream >> value;
		return value;
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
