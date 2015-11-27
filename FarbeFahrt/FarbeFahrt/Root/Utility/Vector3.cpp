# include "Vector3.h"
# include "Vector4.h"
# include "Point3.h"
# include "String.h"
# include "Math.h"

# include "MemoryCast.h"

# include <DxLib.h>

const Vector3& Vector3::Zero()
{
	static Vector3 zero { 0.0f, 0.0f, 0.0f };
	return zero;
}

const Vector3& Vector3::One()
{
	static Vector3 one { 1.0f, 1.0f, 1.0f };
	return one;
}

const Vector3& Vector3::Left()
{
	static Vector3 left { -1.0f, 0.0f, 0.0f };
	return left;
}

const Vector3& Vector3::Right()
{
	static Vector3 right { 1.0f, 0.0f, 0.0f };
	return right;
}

const Vector3& Vector3::Up()
{
	static Vector3 up { 0.0f, 1.0f, 0.0f };
	return up;
}

const Vector3& Vector3::Down()
{
	static Vector3 down { 0.0f, -1.0f, 0.0f };
	return down;
}

const Vector3& Vector3::Forward()
{
	static Vector3 forward { 0.0f, 0.0f, 1.0f };
	return forward;
}

const Vector3& Vector3::backward()
{
	static Vector3 backward { 0.0f, 0.0f, -1.0f };
	return backward;
}

Vector3::Vector3()
	: Vector3(0.0f, 0.0f, 0.0f)
{

}

Vector3::Vector3(const Vector3& v)
	: Vector3(v.x, v.y, v.z)
{

}

Vector3::Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{

}

Vector3::Vector3(const Vector4& v)
	: Vector3(v.x, v.y, v.z)
{

}

Vector3::Vector3(const Point3& v)
	: Vector3(
		static_cast<float>(v.x),
		static_cast<float>(v.y),
		static_cast<float>(v.z))
{
}

Vector3::Vector3(const VECTOR& v)
	: x(v.x)
	, y(v.y)
	, z(v.z)
{

}

Vector3& Vector3::operator = (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3::operator float* ()
{
	return elm;
}

Vector3::operator const float* () const
{
	return elm;
}

Vector3::operator VECTOR&()
{
	return memory_cast<VECTOR>(*this);
}

Vector3::operator const VECTOR&() const
{
	return memory_cast<VECTOR>(*this);
}

std::string Vector3::ToString() const
{
	return toString(*this);
}

float Vector3::dot(const Vector3& v) const
{
	return Dot(*this, v);
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return Cross(*this, v);
}

float Vector3::lengthSquared() const
{
	return LengthSquared(*this);
}

float Vector3::length() const
{
	return Length(*this);
}

Vector3& Vector3::normalize()
{
	*this = Normalize(*this);
	return *this;
}

Vector3& Vector3::rotate(const Vector3& axis, double angle)
{
	*this = Rotate(*this, axis, angle);
	return *this;
}

Vector3& Vector3::projection(const Vector3& v)
{
	*this = Projection(*this, v);
	return *this;
}

float Vector3::angle(const Vector3& v) const
{
	return Angle(*this, v);
}

std::string Vector3::toString(const Vector3& v)
{
	return String::Create("(", v.x, ", ", v.y, ", ", v.z, ")");
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

float Vector3::LengthSquared(const Vector3& v)
{
	return Dot(v, v);
}

float Vector3::Length(const Vector3& v)
{
	return static_cast<float>(Math::Sqrt(LengthSquared(v)));
}

Vector3 Vector3::Normalize(const Vector3& v)
{
	float lengthSq = LengthSquared(v);
	if (lengthSq == 0.0f)
	{
		return v;
	}

	return v / static_cast<float>(Math::Sqrt(lengthSq));
}

Vector3 Vector3::Rotate(const Vector3& point, const Vector3& axis, double angle)
{
	Vector3 v = Dot(point, axis) * Normalize(axis);
	return
		v +
		static_cast<float>(Math::Cos(angle)) * (point - v) +
		static_cast<float>(Math::Sin(angle)) * Cross(point, axis);
}

Vector3 Vector3::Projection(const Vector3& v, const Vector3& target)
{
	Vector3 normal = Normalize(target);
	return Dot(v, normal) * normal;
}

Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, float t)
{
	return start + (end - start) * t;
}

float Vector3::Angle(const Vector3& v1, const Vector3& v2)
{
	return static_cast<float>(Math::Acos(Dot(Normalize(v1), Normalize(v2))));
}

Vector3 Vector3::Slerp(const Vector3& start, const Vector3& end, float t)
{
	return Rotate(start, Cross(end, start), Angle(start, end) * t);
}

bool operator == (const Vector3& v1, const Vector3& v2)
{
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z;
}

bool operator != (const Vector3& v1, const Vector3& v2)
{
	return !(v1 == v2);
}

Vector3 operator + (const Vector3& v)
{
	return v;
}

Vector3 operator - (const Vector3& v)
{
	return Vector3(-v.x, -v.y, -v.z);
}

Vector3& operator += (Vector3& v1, const Vector3& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

Vector3& operator -= (Vector3& v1, const Vector3& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

Vector3& operator *= (Vector3& v1, const Vector3& v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return v1;
}

Vector3& operator *= (Vector3& v, float s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}

Vector3& operator /= (Vector3& v1, const Vector3& v2)
{
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	return v1;
}

Vector3& operator /= (Vector3& v, float s)
{
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return v;
}

Vector3 operator + (const Vector3& v1, const Vector3& v2)
{
	Vector3 result = v1;
	return result += v2;
}

Vector3 operator - (const Vector3& v1, const Vector3& v2)
{
	Vector3 result = v1;
	return result -= v2;
}

Vector3 operator * (const Vector3& v1, const Vector3& v2)
{
	Vector3 result = v1;
	return result *= v2;
}

Vector3 operator * (const Vector3& v, float s)
{
	Vector3 result = v;
	return result *= s;
}

Vector3 operator * (float s, const Vector3& v)
{
	return v * s;
}

Vector3 operator / (const Vector3& v1, const Vector3& v2)
{
	Vector3 result = v1;
	return result /= v2;
}

Vector3 operator / (const Vector3& v, float s)
{
	Vector3 result = v;
	return result /= s;
}
