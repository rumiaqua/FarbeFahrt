# include "Math.h"

# include <cmath>

namespace Math
{
	double ToRadian(double x)
	{
		return x * RADIAN;
	}

	double ToDegree(double x)
	{
		return x * DEGREE;
	}

	double Sin(double x)
	{
		return std::sin(x);
	}

	double Cos(double x)
	{
		return std::cos(x);
	}

	double Tan(double x)
	{
		return std::tan(x);
	}

	double Asin(double x)
	{
		return std::asin(x);
	}

	double Acos(double x)
	{
		return std::acos(x);
	}

	double Atan(double x)
	{
		return std::atan(x);
	}

	double Atan2(double y, double x)
	{
		return std::atan2(y, x);
	}

	double Floor(double x)
	{
		return std::floor(x);
	}

	double Ceiling(double x)
	{
		return std::ceil(x);
	}

	double Round(double x)
	{
		return std::round(x);
	}

	double Sign(double x)
	{
		return std::signbit(x) ? 1.0 : -1.0;
	}

	double Pow(double x, double y)
	{
		return std::pow(x, y);
	}

	double Sqrt(double x)
	{
		return std::sqrt(x);
	}

	double Smooth(double x, int y)
	{
		double f = Math::Pow(10.0, -static_cast<double>(y));
		int i = (int)(x * f);
		return i / f;
	}

	double Saturate(double x)
	{
		return Clamp(x, 0.0, 1.0);
	}

	double Clamp(double x, double y, double z)
	{
		return Math::Min({ Math::Max({ x, y }), z });
	}
}
