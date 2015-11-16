# include "Vector2.h"
# include "Vector3.h"
# include "Point2.h"
# include "String.h"
# include "Math.h"

const Vector2& Vector2::Zero()
{
	static Vector2 zero { 0.0f, 0.0f };
	return zero;
}

const Vector2& Vector2::One()
{
	static Vector2 one { 1.0f, 1.0f };
	return one;
}

const Vector2& Vector2::Left()
{
	static Vector2 left { -1.0f, 0.0f };
	return left;
}

const Vector2& Vector2::Right()
{
	static Vector2 right { 1.0f, 0.0f };
	return right;
}

const Vector2& Vector2::Up()
{
	static Vector2 up { 0.0f, -1.0f };
	return up;
}

const Vector2& Vector2::Down()
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
	return ToString(*this);
}

float Vector2::dot(const Vector2& v) const
{
	return Dot(*this, v);
}

float Vector2::cross(const Vector2& v) const
{
	return Cross(*this, v);
}

float Vector2::lengthSquared() const
{
	return LengthSquared(*this);
}

float Vector2::length() const
{
	return Length(*this);
}

Vector2& Vector2::normalize()
{
	*this =Nornalize(*this);
	return *this;
}

Vector2& Vector2::rotate(const Vector2& origin, double angle)
{
	*this = Rotate(*this, origin, angle);
	return *this;
}

Vector2& Vector2::projection(const Vector2& v)
{
	*this = Projection(*this, v);
	return *this;
}

float Vector2::angle(const Vector2& v) const
{
	return Angle(*this, v);
}

String Vector2::ToString(const Vector2& v)
{
	return String::Create("(", v.x, ", ", v.y, ")");
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

float Vector2::LengthSquared(const Vector2& v)
{
	return Dot(v, v);
}

float Vector2::Length(const Vector2& v)
{
	return static_cast<float>(Math::Sqrt(LengthSquared(v)));
}

Vector2 Vector2::Nornalize(const Vector2& v)
{
	float lengthSq = LengthSquared(v);
	if (lengthSq == 0.0f)
	{
		return v;
	}

	return v / static_cast<float>(Math::Sqrt(lengthSq));
}

Vector2 Vector2::Rotate(const Vector2& point, const Vector2& origin, double angle)
{
	return origin + (point - origin) * Vector2(
			static_cast<float>(Math::Cos(angle)),
			static_cast<float>(Math::Sin(angle)));
}

Vector2 Vector2::Projection(const Vector2& v, const Vector2& target)
{
	Vector2 normal = Nornalize(target);
	return Dot(v, normal) * normal;
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, float t)
{
	return start + (end - start) * t;
}

float Vector2::Angle(const Vector2& v1, const Vector2& v2)
{
	return static_cast<float>(Math::Acos(Dot(Nornalize(v1), Nornalize(v2))));
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
