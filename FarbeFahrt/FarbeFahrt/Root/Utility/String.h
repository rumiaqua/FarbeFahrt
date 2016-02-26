# pragma once

# include <string>
# include <vector>
# include <sstream>

namespace String
{
	std::string Create(const char* value);

	std::string Create(const std::string& value);

	std::string Create(long double value);

	std::string Create(double value);

	std::string Create(float value);

	std::string Create(unsigned long long value);

	std::string Create(long long value);

	std::string Create(unsigned long value);

	std::string Create(long value);

	std::string Create(unsigned int value);

	std::string Create(int value);

	std::string Create(bool value);

	template <typename Type, typename ...Args>
	std::string Create(const Type& value, Args&& ...args)
	{
		return Create(value) + Create(std::forward<Args>(args)...);
	}

	std::vector<std::string> Split(const std::string& str, char delim);

	template <typename Type>
	Type ToValue(const std::string& str)
	{
		std::stringstream stream(str);
		Type value;
		stream >> value;
		return value;
	}

	std::wstring ToWide(std::string const& narrow);

	std::string ToNarrow(std::wstring const& wide);
}
