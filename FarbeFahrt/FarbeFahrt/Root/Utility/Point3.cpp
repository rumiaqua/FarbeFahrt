# include "Point3.h"
# include "Point4.h"
# include "Vector3.h"
# include "String.h"
# include "Math.h"

const Point3& Point3::zero()
{
	static Point3 zero { 0, 0, 0 };
	return zero;
}

const Point3& Point3::one()
{
	static Point3 one { 1, 1, 1 };
	return one;
}

const Point3& Point3::left()
{
	static Point3 left { -1, 0, 0 };
	return left;
}

const Point3& Point3::right()
{
	static Point3 right { 1, 0, 0 };
	return right;
}

const Point3& Point3::up()
{
	static Point3 up { 0, 1, 0 };
	return up;
}

const Point3& Point3::down()
{
	static Point3 down { 0, -1, 0 };
	return down;
}

const Point3& Point3::forward()
{
	static Point3 forward { 0, 0, 1 };
	return forward;
}

const Point3& Point3::backward()
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
	return toString(*this);
}

int Point3::dot(const Point3& v) const
{
	return dot(*this, v);
}

Point3 Point3::cross(const Point3& v) const
{
	return cross(*this, v);
}

int Point3::lengthSquared() const
{
	return lengthSquared(*this);
}

float Point3::length() const
{
	return length(*this);
}

String Point3::toString(const Point3& v)
{
	return String::create("(", v.x, ", ", v.y, ", ", v.z, ")");
}

int Point3::dot(const Point3& v1, const Point3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Point3 Point3::cross(const Point3& v1, const Point3& v2)
{
	return Point3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

int Point3::lengthSquared(const Point3& v)
{
	return dot(v, v);
}

float Point3::length(const Point3& v)
{
	return static_cast<float>(Math::sqrt(lengthSquared(v)));
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
