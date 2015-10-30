# include "Vector2.h"
# include "Vector3.h"
# include "Point2.h"
# include "String.h"
# include "Math.h"

const Vector2& Vector2::zero()
{
	static Vector2 zero { 0.0f, 0.0f };
	return zero;
}

const Vector2& Vector2::one()
{
	static Vector2 one { 1.0f, 1.0f };
	return one;
}

const Vector2& Vector2::left()
{
	static Vector2 left { -1.0f, 0.0f };
	return left;
}

const Vector2& Vector2::right()
{
	static Vector2 right { 1.0f, 0.0f };
	return right;
}

const Vector2& Vector2::up()
{
	static Vector2 up { 0.0f, -1.0f };
	return up;
}

const Vector2& Vector2::down()
{
	static Vector2 down { 0.0f, 1.0f };
	return down;
}

Vector2::Vector2()
	: Vector2(0.0f, 0.0f)
{

}

Vector2::Vector2(const Vector2& v)
	: Vector2(v.x, v.y)
{

}

Vector2::Vector2(float x, float y)
	: x(x)
	, y(y)
{

}

Vector2::Vector2(const Vector3& v)
	: Vector2(v.x, v.y)
{

}

Vector2::Vector2(const Point2& v)
	: Vector2(
		static_cast<float>(v.x),
		static_cast<float>(v.y))
{

}

Vector2& Vector2::operator = (const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2::operator float* ()
{
	return elm;
}

Vector2::operator const float* () const
{
	return elm;
}

String Vector2::toString() const
{
	return toString(*this);
}

float Vector2::dot(const Vector2& v) const
{
	return dot(*this, v);
}

float Vector2::cross(const Vector2& v) const
{
	return cross(*this, v);
}

float Vector2::lengthSquared() const
{
	return lengthSquared(*this);
}

float Vector2::length() const
{
	return length(*this);
}

Vector2& Vector2::normalize()
{
	*this =normalize(*this);
	return *this;
}

Vector2& Vector2::rotate(const Vector2& origin, float angle)
{
	*this = rotate(*this, origin, angle);
	return *this;
}

Vector2& Vector2::projection(const Vector2& v)
{
	*this = projection(*this, v);
	return *this;
}

float Vector2::angle(const Vector2& v) const
{
	return angle(*this, v);
}

String Vector2::toString(const Vector2& v)
{
	return String::Create("(", v.x, ", ", v.y, ")");
}

float Vector2::dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::cross(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

float Vector2::lengthSquared(const Vector2& v)
{
	return dot(v, v);
}

float Vector2::length(const Vector2& v)
{
	return static_cast<float>(Math::sqrt(lengthSquared(v)));
}

Vector2 Vector2::normalize(const Vector2& v)
{
	float lengthSq = lengthSquared(v);
	if (lengthSq == 0.0f)
	{
		return v;
	}

	return v / static_cast<float>(Math::sqrt(lengthSq));
}

Vector2 Vector2::rotate(const Vector2& point, const Vector2& origin, float angle)
{
	return origin + (point - origin) * Vector2(
			static_cast<float>(Math::cos(angle)),
			static_cast<float>(Math::sin(angle)));
}

Vector2 Vector2::projection(const Vector2& v, const Vector2& target)
{
	Vector2 normal = normalize(target);
	return dot(v, normal) * normal;
}

Vector2 Vector2::lerp(const Vector2& start, const Vector2& end, float t)
{
	return start + (end - start) * t;
}

float Vector2::angle(const Vector2& v1, const Vector2& v2)
{
	return static_cast<float>(Math::acos(dot(normalize(v1), normalize(v2))));
}

bool operator == (const Vector2& v1, const Vector2& v2)
{
	return
		v1.x == v2.x &&
		v1.y == v2.y;
}

bool operator != (const Vector2& v1, const Vector2& v2)
{
	return !(v1 == v2);
}

Vector2 operator + (const Vector2& v)
{
	return v;
}

Vector2 operator - (const Vector2& v)
{
	return Vector2(-v.x, -v.y);
}

Vector2& operator += (Vector2& v1, const Vector2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2& operator -= (Vector2& v1, const Vector2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2& operator *= (Vector2& v1, const Vector2& v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	return v1;
}

Vector2& operator *= (Vector2& v, float s)
{
	v.x *= s;
	v.y *= s;
	return v;
}

Vector2& operator /= (Vector2& v1, const Vector2& v2)
{
	v1.x /= v2.x;
	v1.y /= v2.y;
	return v1;
}

Vector2& operator /= (Vector2& v, float s)
{
	v.x /= s;
	v.y /= s;
	return v;
}

Vector2 operator + (const Vector2& v1, const Vector2& v2)
{
	Vector2 result = v1;
	return result += v2;
}

Vector2 operator - (const Vector2& v1, const Vector2& v2)
{
	Vector2 result = v1;
	return result -= v2;
}

Vector2 operator * (const Vector2& v1, const Vector2& v2)
{
	Vector2 result = v1;
	return result *= v2;
}

Vector2 operator * (const Vector2& v, float s)
{
	Vector2 result = v;
	return result *= s;
}

Vector2 operator * (float s, const Vector2& v)
{
	return v * s;
}

Vector2 operator / (const Vector2& v1, const Vector2& v2)
{
	Vector2 result = v1;
	return result /= v2;
}

Vector2 operator / (const Vector2& v, float s)
{
	Vector2 result = v;
	return result /= s;
}
