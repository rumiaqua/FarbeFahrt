# include "String.h"

# include <Windows.h>

String::String()
	: m_str()
{

}

String::String(const char* str)
	: String(std::string(str))
{

}

String::String(const wchar_t* str)
	: m_str(str)
{

}

String::String(const std::string& str)
	: m_str(toWide(str))
{

}

String::String(const std::wstring& str)
	: m_str(str)
{

}

String& String::operator = (const String& str)
{
	m_str = str.m_str;
	return *this;
}

wchar_t String::operator[](unsigned int index) const
{
	return m_str[index];
}

unsigned int String::length() const
{
	return length(*this);
}

std::wstring String::toWide() const
{
	return toWide(*this);
}

std::string String::toNarrow() const
{
	return toNarrow(*this);
}

const char* const String::c_str() const
{
	return c_str(*this);
}

const wchar_t* const String::w_str() const
{
	return w_str(*this);
}

std::wstring String::toWide(const std::string& narrow)
{
	int length =
		MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, NULL, 0);
	wchar_t* buffer = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, buffer, length);
	std::wstring result(buffer, buffer + length - 1);
	delete[] buffer;
	return result;
}

std::string String::toNarrow(const std::wstring& wide)
{
	int length = WideCharToMultiByte(
		CP_OEMCP, 0, wide.c_str(), -1, NULL, 0, NULL, NULL);
	char* buffer = new char[length];
	WideCharToMultiByte(
		CP_OEMCP, 0, wide.c_str(), -1, buffer, length, NULL, NULL);
	std::string result(buffer, buffer + length - 1);
	delete[] buffer;
	return result;
}

unsigned int String::length(const String& str)
{
	return (unsigned int)str.m_str.length();
}

std::string String::toNarrow(const String& str)
{
	return toNarrow(str.m_str);
}

std::wstring String::toWide(const String& str)
{
	return str.m_str;
}

const char* const String::c_str(const String& str)
{
	return toNarrow(str).c_str();
}

const wchar_t * const String::w_str(const String& str)
{
	return toWide(str).c_str();
}

String String::create(const String& value)
{
	return value;
}

String String::create(const char* value)
{
	return String(value);
}

String String::create(const wchar_t* value)
{
	return String(value);
}

String String::create(const std::string& value)
{
	return String(value);
}

String String::create(const std::wstring& value)
{
	return String(value);
}

String String::create(long double value)
{
	return std::to_string(value);
}

String String::create(double value)
{
	return std::to_string(value);
}

String String::create(float value)
{
	return std::to_string(value);
}

String String::create(unsigned long long value)
{
	return std::to_string(value);
}

String String::create(long long value)
{
	return std::to_string(value);
}

String String::create(unsigned long value)
{
	return std::to_string(value);
}

String String::create(long value)
{
	return std::to_string(value);
}

String String::create(unsigned int value)
{
	return std::to_string(value);
}

String String::create(int value)
{
	return std::to_string(value);
}

bool String::operator == (const String& str) const
{
	return m_str == str.m_str;
}

bool String::operator != (const String& str) const
{
	return !(*this == str);
}

String& String::operator += (const String& str)
{
	m_str.append(str.m_str);
	return *this;
}

String String::operator + (const String& str) const
{
	String result = *this;
	return result += str;
}

std::ostream& operator << (std::ostream& stream, const String& str)
{
	stream << String::toNarrow(str);
	return stream;
}
