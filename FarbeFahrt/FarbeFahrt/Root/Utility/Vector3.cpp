# include "Vector3.h"
# include "Vector4.h"
# include "Point3.h"
# include "String.h"
# include "Math.h"

# include "MemoryCast.h"

# include <DxLib.h>

const Vector3& Vector3::zero()
{
	static Vector3 zero { 0.0f, 0.0f, 0.0f };
	return zero;
}

const Vector3& Vector3::one()
{
	static Vector3 one { 1.0f, 1.0f, 1.0f };
	return one;
}

const Vector3& Vector3::left()
{
	static Vector3 left { -1.0f, 0.0f, 0.0f };
	return left;
}

const Vector3& Vector3::right()
{
	static Vector3 right { 1.0f, 0.0f, 0.0f };
	return right;
}

const Vector3& Vector3::up()
{
	static Vector3 up { 0.0f, 1.0f, 0.0f };
	return up;
}

const Vector3& Vector3::down()
{
	static Vector3 down { 0.0f, -1.0f, 0.0f };
	return down;
}

const Vector3& Vector3::forward()
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

String Vector3::toString() const
{
	return toString(*this);
}

float Vector3::dot(const Vector3& v) const
{
	return dot(*this, v);
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return cross(*this, v);
}

float Vector3::lengthSquared() const
{
	return lengthSquared(*this);
}

float Vector3::length() const
{
	return length(*this);
}

Vector3& Vector3::normalize()
{
	*this = normalize(*this);
	return *this;
}

Vector3& Vector3::rotate(const Vector3& axis, float angle)
{
	*this = rotate(*this, axis, angle);
	return *this;
}

Vector3& Vector3::projection(const Vector3& v)
{
	*this = projection(*this, v);
	return *this;
}

float Vector3::angle(const Vector3& v) const
{
	return angle(*this, v);
}

String Vector3::toString(const Vector3& v)
{
	return String::create("(", v.x, ", ", v.y, ", ", v.z, ")");
}

float Vector3::dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

float Vector3::lengthSquared(const Vector3& v)
{
	return dot(v, v);
}

float Vector3::length(const Vector3& v)
{
	return static_cast<float>(Math::sqrt(lengthSquared(v)));
}

Vector3 Vector3::normalize(const Vector3& v)
{
	float lengthSq = lengthSquared(v);
	if (lengthSq == 0.0f)
	{
		return v;
	}

	return v / static_cast<float>(Math::sqrt(lengthSq));
}

Vector3 Vector3::rotate(const Vector3& point, const Vector3& axis, float angle)
{
	Vector3 v = dot(point, axis) * normalize(axis);
	return
		v +
		static_cast<float>(Math::cos(angle)) * (point - v) +
		static_cast<float>(Math::sin(angle)) * cross(point, axis);
}

Vector3 Vector3::projection(const Vector3& v, const Vector3& target)
{
	Vector3 normal = normalize(target);
	return dot(v, normal) * normal;
}

Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, float t)
{
	return start + (end - start) * t;
}

float Vector3::angle(const Vector3& v1, const Vector3& v2)
{
	return static_cast<float>(Math::acos(dot(normalize(v1), normalize(v2))));
}

Vector3 Vector3::slerp(const Vector3& start, const Vector3& end, float t)
{
	return rotate(start, cross(end, start), angle(start, end) * t);
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