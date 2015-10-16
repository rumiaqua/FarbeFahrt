# include "Math.h"

# include <cmath>

namespace Math
{
	double toRadian(double x)
	{
		return x * Radian;
	}

	double toDegree(double x)
	{
		return x * Degree;
	}

	double sin(double x)
	{
		return std::sin(x);
	}

	double cos(double x)
	{
		return std::cos(x);
	}

	double tan(double x)
	{
		return std::tan(x);
	}

	double asin(double x)
	{
		return std::asin(x);
	}

	double acos(double x)
	{
		return std::acos(x);
	}

	double atan(double x)
	{
		return std::atan(x);
	}

	double atan2(double y, double x)
	{
		return std::atan2(y, x);
	}

	double floor(double x)
	{
		return std::floor(x);
	}

	double ceiling(double x)
	{
		return std::ceil(x);
	}

	double round(double x)
	{
		return std::round(x);
	}

	double sign(double x)
	{
		return std::signbit(x) ? 1.0 : -1.0;
	}

	double pow(double x, double y)
	{
		return std::pow(x, y);
	}

	double sqrt(double x)
	{
		return std::sqrt(x);
	}

	double smooth(double x, int y)
	{
		double f = Math::pow(10.0, -static_cast<double>(y));
		int i = (int)(x * f);
		return i / f;
	}

	double saturate(double x)
	{
		return clamp(x, 0.0, 1.0);
	}

	double clamp(double x, double y, double z)
	{
		return Math::minElement({ Math::maxElement({ x, y }), z });
	}
}
