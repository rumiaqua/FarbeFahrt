# include "String.h"

# include <Windows.h>

namespace String
{
	std::string Create(const char* value)
	{
		return std::string(value);
	}

	std::string Create(const std::string& value)
	{
		return value;
	}

	std::string Create(long double value)
	{
		return std::to_string(value);
	}

	std::string Create(double value)
	{
		return std::to_string(value);
	}

	std::string Create(float value)
	{
		return std::to_string(value);
	}

	std::string Create(unsigned long long value)
	{
		return std::to_string(value);
	}

	std::string Create(long long value)
	{
		return std::to_string(value);
	}

	std::string Create(unsigned long value)
	{
		return std::to_string(value);
	}

	std::string Create(long value)
	{
		return std::to_string(value);
	}

	std::string Create(unsigned int value)
	{
		return std::to_string(value);
	}

	std::string Create(int value)
	{
		return std::to_string(value);
	}

	std::vector<std::string> Split(const std::string& str, char delim)
	{
		std::vector<std::string> res;
		size_t current = 0, found;
		std::string s = str;
		while ((found = s.find_first_of(delim, current)) != std::string::npos)
		{
			res.push_back(std::string(s, current, found - current));
			current = found + 1;
		}
		res.push_back(std::string(s, current, s.size() - current));
		return res;
	}

	std::wstring ToWide(std::string const& narrow)
	{
		int length =
			MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, NULL, 0);
		wchar_t* buffer = new wchar_t[length];
		MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, buffer, length);
		std::wstring result(buffer, buffer + length - 1);
		delete[] buffer;
		return result;
	}

	std::string ToNarrow(std::wstring const& wide)
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
}
