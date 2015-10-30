# include "Point2.h"
# include "Point3.h"
# include "Vector2.h"
# include "String.h"
# include "Math.h"
# include "MemoryCast.h"

const Point2& Point2::zero()
{
	static Point2 zero { 0, 0 };
	return zero;
}

const Point2& Point2::one()
{
	static Point2 one { 1, 1 };
	return one;
}

const Point2& Point2::left()
{
	static Point2 left { -1, 0 };
	return left;
}

const Point2& Point2::right()
{
	static Point2 right { 1, 0 };
	return right;
}

const Point2& Point2::up()
{
	static Point2 up { 0, -1 };
	return up;
}

const Point2& Point2::down()
{
	static Point2 down { 0, 1 };
	return down;
}

Point2::Point2()
	: Point2(0, 0)
{

}

Point2::Point2(const Point2& v)
	: Point2(v.x, v.y)
{

}

Point2::Point2(int x, int y)
	: x(x)
	, y(y)
{

}

Point2::Point2(const Point3& v)
	: Point2(v.x, v.y)
{

}

Point2::Point2(const Vector2& v)
	: Point2(
		static_cast<int>(v.x),
		static_cast<int>(v.y))
{
}

Point2::Point2(const POINT& p)
	: x(p.x)
	, y(p.y)
{

}

Point2& Point2::operator = (const Point2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Point2::operator int* ()
{
	return elm;
}

Point2::operator const int* () const
{
	return elm;
}

Point2::operator POINT& ()
{
	return memory_cast<POINT>(*this);
}

Point2::operator const POINT& () const
{
	return memory_cast<POINT>(*this);
}

String Point2::toString() const
{
	return toString(*this);
}

int Point2::dot(const Point2& v) const
{
	return dot(*this, v);
}

int Point2::cross(const Point2& v) const
{
	return cross(*this, v);
}

int Point2::lengthSquared() const
{
	return lengthSquared(*this);
}

float Point2::length() const
{
	return length(*this);
}

String Point2::toString(const Point2& v)
{
	return String::Create("(", v.x, ", ", v.y, ")");
}

int Point2::dot(const Point2& v1, const Point2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

int Point2::cross(const Point2& v1, const Point2& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

int Point2::lengthSquared(const Point2& v)
{
	return dot(v, v);
}

float Point2::length(const Point2& v)
{
	return static_cast<float>(Math::sqrt(lengthSquared(v)));
}

bool operator == (const Point2& v1, const Point2& v2)
{
	return
		v1.x == v2.x &&
		v1.y == v2.y;
}

bool operator != (const Point2& v1, const Point2& v2)
{
	return !(v1 == v2);
}

Point2 operator + (const Point2& v)
{
	return v;
}

Point2 operator - (const Point2& v)
{
	return Point2(-v.x, -v.y);
}

Point2& operator += (Point2& v1, const Point2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Point2& operator -= (Point2& v1, const Point2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Point2& operator *= (Point2& v1, const Point2& v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	return v1;
}

Point2& operator *= (Point2& v, int s)
{
	v.x *= s;
	v.y *= s;
	return v;
}

Point2& operator /= (Point2& v1, const Point2& v2)
{
	v1.x /= v2.x;
	v1.y /= v2.y;
	return v1;
}

Point2& operator /= (Point2& v, int s)
{
	v.x /= s;
	v.y /= s;
	return v;
}

Point2 operator + (const Point2& v1, const Point2& v2)
{
	Point2 result = v1;
	return result += v2;
}

Point2 operator - (const Point2& v1, const Point2& v2)
{
	Point2 result = v1;
	return result -= v2;
}

Point2 operator * (const Point2& v1, const Point2& v2)
{
	Point2 result = v1;
	return result *= v2;
}

Point2 operator * (const Point2& v, int s)
{
	Point2 result = v;
	return result *= s;
}

Point2 operator * (int s, const Point2& v)
{
	return v * s;
}

Point2 operator / (const Point2& v1, const Point2& v2)
{
	Point2 result = v1;
	return result /= v2;
}

Point2 operator / (const Point2& v, int s)
{
	Point2 result = v;
	return result /= s;
}
