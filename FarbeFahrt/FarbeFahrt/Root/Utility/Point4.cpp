# include "Point4.h"
# include "Point3.h"
# include "Vector4.h"
# include "Math.h"
# include "String.h"

const Point4& Point4::zero()
{
	static Point4 zero { 0, 0, 0, 0 };
	return zero;
}

const Point4& Point4::one()
{
	static Point4 one { 1, 1, 1, 1 };
	return one;
}

Point4::Point4()
	: Point4(0, 0, 0, 0)
{

}

Point4::Point4(const Point4& v)
	: Point4(v.x, v.y, v.z, v.w)
{

}

Point4::Point4(int x, int y, int z, int w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{

}

Point4::Point4(const Point3& v, int w)
	: Point4(v.x, v.y, v.z, w)
{

}

Point4::Point4(const Vector4& v)
	: Point4(
		static_cast<int>(v.x),
		static_cast<int>(v.y),
		static_cast<int>(v.z),
		static_cast<int>(v.w))
{
}

Point4& Point4::operator = (const Point4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

Point4::operator int* ()
{
	return elm;
}

Point4::operator const int* () const
{
	return elm;
}

std::string Point4::toString() const
{
	return ToString(*this);
}

int Point4::dot(const Point4& v) const
{
	return Dot(*this, v);
}

int Point4::lengthSquared() const
{
	return LengthSquared(*this);
}

float Point4::length() const
{
	return Length(*this);
}

int Point4::Dot(const Point4& v1, const Point4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

int Point4::LengthSquared(const Point4& v)
{
	return Dot(v, v);
}

float Point4::Length(const Point4& v)
{
	return static_cast<float>(Math::Sqrt(LengthSquared(v)));
}

std::string Point4::ToString(const Point4& v)
{
	return String::Create("(", v.x, ", ", v.y, ", ", v.z, ", ", v.w, ")");
}

bool operator == (const Point4& v1, const Point4& v2)
{
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z &&
		v1.w == v2.w;
}

bool operator != (const Point4& v1, const Point4& v2)
{
	return !(v1 == v2);
}

Point4 operator + (const Point4& v)
{
	return v;
}

Point4 operator - (const Point4& v)
{
	return Point4(-v.x, -v.y, -v.z, -v.w);
}

Point4& operator += (Point4& v1, const Point4& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}

Point4& operator -= (Point4& v1, const Point4& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return v1;
}

Point4& operator *= (Point4& v1, const Point4& v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	v1.w *= v2.w;
	return v1;
}

Point4& operator *= (Point4& v, int s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	v.w *= s;
	return v;
}

Point4& operator /= (Point4& v1, const Point4& v2)
{
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	v1.w /= v2.w;
	return v1;
}

Point4& operator /= (Point4& v, int s)
{
	v.x /= s;
	v.y /= s;
	v.z /= s;
	v.w /= s;
	return v;
}

Point4 operator + (const Point4& v1, const Point4& v2)
{
	Point4 result = v1;
	return result += v2;
}

Point4 operator - (const Point4& v1, const Point4& v2)
{
	Point4 result = v1;
	return result -= v2;
}

Point4 operator * (const Point4& v1, const Point4& v2)
{
	Point4 result = v1;
	return result *= v2;
}

Point4 operator * (const Point4& v, int s)
{
	Point4 result = v;
	return result *= s;
}

Point4 operator * (int s, const Point4& v)
{
	return v * s;
}

Point4 operator / (const Point4& v1, const Point4& v2)
{
	Point4 result = v1;
	return result /= v2;
}

Point4 operator / (const Point4& v, int s)
{
	Point4 result = v;
	return result /= s;
}
