# include "Point3.h"
# include "Point4.h"
# include "Vector3.h"
# include "String.h"
# include "Math.h"

const Point3& Point3::Zero()
{
	static Point3 zero { 0, 0, 0 };
	return zero;
}

const Point3& Point3::One()
{
	static Point3 one { 1, 1, 1 };
	return one;
}

const Point3& Point3::Left()
{
	static Point3 left { -1, 0, 0 };
	return left;
}

const Point3& Point3::Right()
{
	static Point3 right { 1, 0, 0 };
	return right;
}

const Point3& Point3::Up()
{
	static Point3 up { 0, 1, 0 };
	return up;
}

const Point3& Point3::Down()
{
	static Point3 down { 0, -1, 0 };
	return down;
}

const Point3& Point3::Forward()
{
	static Point3 forward { 0, 0, 1 };
	return forward;
}

const Point3& Point3::Backward()
{
	static Point3 backward { 0, 0, -1 };
	return backward;
}

Point3::Point3()
	: Point3(0, 0, 0)
{

}

Point3::Point3(const Point3& v)
	: Point3(v.x, v.y, v.z)
{

}

Point3::Point3(int x, int y, int z)
	: x(x)
	, y(y)
	, z(z)
{

}

Point3::Point3(const Point4& v)
	: Point3(v.x, v.y, v.z)
{

}

Point3::Point3(const Vector3& v)
	: Point3(
		static_cast<int>(v.x),
		static_cast<int>(v.y),
		static_cast<int>(v.z))
{
}

Point3& Point3::operator = (const Point3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Point3::operator int* ()
{
	return elm;
}

Point3::operator const int* () const
{
	return elm;
}

String Point3::toString() const
{
	return ToString(*this);
}

int Point3::dot(const Point3& v) const
{
	return Dot(*this, v);
}

Point3 Point3::cross(const Point3& v) const
{
	return Cross(*this, v);
}

int Point3::lengthSquared() const
{
	return LengthSquared(*this);
}

float Point3::length() const
{
	return Length(*this);
}

String Point3::ToString(const Point3& v)
{
	return String::Create("(", v.x, ", ", v.y, ", ", v.z, ")");
}

int Point3::Dot(const Point3& v1, const Point3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Point3 Point3::Cross(const Point3& v1, const Point3& v2)
{
	return Point3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

int Point3::LengthSquared(const Point3& v)
{
	return Dot(v, v);
}

float Point3::Length(const Point3& v)
{
	return static_cast<float>(Math::Sqrt(LengthSquared(v)));
}

bool operator == (const Point3& v1, const Point3& v2)
{
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z;
}

bool operator != (const Point3& v1, const Point3& v2)
{
	return !(v1 == v2);
}

Point3 operator + (const Point3& v)
{
	return v;
}

Point3 operator - (const Point3& v)
{
	return Point3(-v.x, -v.y, -v.z);
}

Point3& operator += (Point3& v1, const Point3& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

Point3& operator -= (Point3& v1, const Point3& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

Point3& operator *= (Point3& v1, const Point3& v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return v1;
}

Point3& operator *= (Point3& v, int s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}

Point3& operator /= (Point3& v1, const Point3& v2)
{
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	return v1;
}

Point3& operator /= (Point3& v, int s)
{
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return v;
}

Point3 operator + (const Point3& v1, const Point3& v2)
{
	Point3 result = v1;
	return result += v2;
}

Point3 operator - (const Point3& v1, const Point3& v2)
{
	Point3 result = v1;
	return result -= v2;
}

Point3 operator * (const Point3& v1, const Point3& v2)
{
	Point3 result = v1;
	return result *= v2;
}

Point3 operator * (const Point3& v, int s)
{
	Point3 result = v;
	return result *= s;
}

Point3 operator * (int s, const Point3& v)
{
	return v * s;
}

Point3 operator / (const Point3& v1, const Point3& v2)
{
	Point3 result = v1;
	return result /= v2;
}

Point3 operator / (const Point3& v, int s)
{
	Point3 result = v;
	return result /= s;
}
