# pragma once

# include <string>

class String
{
public:

	/// <summary>�f�t�H���g�R���X�g���N�^</summary>
	String();

	/// <summary>�}���`�o�C�g������ŏ�����</summary>
	/// <param name="str">�}���`�o�C�g������</param>
	String(const char* str);

	/// <summary>���C�h������ŏ�����</summary>
	/// <param name="str">���C�h������</param>
	String(const wchar_t* str);

	/// <summary>string�N���X�ŏ�����</summary>
	/// <param name="str">string�N���X</param>
	String(const std::string& str);

	/// <summary>wstring�N���X�ŏ�����</summary>
	/// <param name="str">wstring�N���X</param>
	String(const std::wstring& str);

public:

	/// <summary>������Z�q</summary>
	/// <param name="str">������</param>
	String& operator = (const String& str);

	/// <summary>�w�肵���C���f�b�N�X�̕�����Ԃ�</summary>
	/// <param name="index">�C���f�b�N�X</param>
	wchar_t operator [] (unsigned int index) const;

public:

	/// <summary>������̒�����Ԃ�</summary>
	unsigned int length() const;

	/// <summary>���C�h�������Ԃ�</summary>
	std::wstring toWide() const;

	/// <summary>�}���`�o�C�g�������Ԃ�</summary>
	std::string toNarrow() const;

public:

	/// <summary>������̒�����Ԃ�</summary>
	/// <param name="str">������</param>
	static unsigned int length(const String& str);

	/// <summary>���C�h������ɕϊ�����</summary>
	/// <param name="narrow">�}���`�o�C�g������</param>
	static std::wstring toWide(const std::string& narrow);

	/// <summary>�}���`�o�C�g������ɕϊ�����</summary>
	/// <param name="wide">���C�h������</param>
	static std::string toNarrow(const std::wstring& wide);

	/// <summary>�}���`�o�C�g�������Ԃ�</summary>
	/// <param name="str">������</param>
	static std::string toNarrow(const String& str);

	/// <summary>���C�h�������Ԃ�</summary>
	/// <param name="str">������</param>
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

	/// <summary>wstring�N���X</summary>
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
