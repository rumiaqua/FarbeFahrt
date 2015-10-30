# include "Vector4.h"
# include "Vector3.h"
# include "Point4.h"
# include "Math.h"
# include "String.h"

const Vector4& Vector4::zero()
{
	static Vector4 zero { 0.0f, 0.0f, 0.0f, 0.0f };
	return zero;
}

const Vector4& Vector4::one()
{
	static Vector4 one { 1.0f, 1.0f, 1.0f, 1.0f };
	return one;
}

Vector4::Vector4()
	: Vector4(0.0f, 0.0f, 0.0f, 0.0f)
{

}

Vector4::Vector4(const Vector4& v)
	: Vector4(v.x, v.y, v.z, v.w)
{

}

Vector4::Vector4(float x, float y, float z, float w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{

}

Vector4::Vector4(const Vector3& v, float w)
	: Vector4(v.x, v.y, v.z, w)
{

}

Vector4::Vector4(const Point4& v)
	: Vector4(
		static_cast<float>(v.x),
		static_cast<float>(v.y),
		static_cast<float>(v.z),
		static_cast<float>(v.w))
{

}

Vector4& Vector4::operator = (const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

Vector4::operator float* ()
{
	return elm;
}

Vector4::operator const float* () const
{
	return elm;
}

String Vector4::toString() const
{
	return toString(*this);
}

 float Vector4::dot(const Vector4& v) const
{
	return dot(*this, v);
}

 float Vector4::lengthSquared() const
{
	return lengthSquared(*this);
}

 float Vector4::length() const
{
	return length(*this);
}

Vector4& Vector4::normalize()
{
	*this = normalize(*this);
	return *this;
}

Vector4& Vector4::projection(const Vector4& v)
{
	*this = projection(*this, v);
	return *this;
}


float Vector4::dot(const Vector4& v1, const Vector4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

float Vector4::lengthSquared(const Vector4& v)
{
	return dot(v, v);
}

float Vector4::length(const Vector4& v)
{
	return static_cast<float>(Math::sqrt(lengthSquared(v)));
}

Vector4 Vector4::normalize(const Vector4& v)
{
	float lengthSq = lengthSquared(v);
	if (lengthSq == 0.0f)
	{
		return v;
	}

	return v / static_cast<float>(Math::sqrt(lengthSq));
}

Vector4 Vector4::projection(const Vector4& v, const Vector4& target)
{
	Vector4 normal = normalize(target);
	return dot(v, normal) * normal;
}

Vector4 Vector4::lerp(const Vector4& start, const Vector4& end, float t)
{
	return start + (end - start) * t;
}

String Vector4::toString(const Vector4& v)
{
	return String::Create("(", v.x, ", ", v.y, ", ", v.z, ", ", v.w, ")");
}

bool operator == (const Vector4& v1, const Vector4& v2)
{
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z &&
		v1.w == v2.w;
}

bool operator != (const Vector4& v1, const Vector4& v2)
{
	return !(v1 == v2);
}

Vector4 operator + (const Vector4& v)
{
	return v;
}

Vector4 operator - (const Vector4& v)
{
	return Vector4(-v.x, -v.y, -v.z, -v.w);
}

Vector4& operator += (Vector4& v1, const Vector4& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}

Vector4& operator -= (Vector4& v1, const Vector4& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return v1;
}

Vector4& operator *= (Vector4& v1, const Vector4& v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	v1.w *= v2.w;
	return v1;
}

Vector4& operator *= (Vector4& v, float s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	v.w *= s;
	return v;
}

Vector4& operator /= (Vector4& v1, const Vector4& v2)
{
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	v1.w /= v2.w;
	return v1;
}

Vector4& operator /= (Vector4& v, float s)
{
	v.x /= s;
	v.y /= s;
	v.z /= s;
	v.w /= s;
	return v;
}

Vector4 operator + (const Vector4& v1, const Vector4& v2)
{
	Vector4 result = v1;
	return result += v2;
}

Vector4 operator - (const Vector4& v1, const Vector4& v2)
{
	Vector4 result = v1;
	return result -= v2;
}

Vector4 operator * (const Vector4& v1, const Vector4& v2)
{
	Vector4 result = v1;
	return result *= v2;
}

Vector4 operator * (const Vector4& v, float s)
{
	Vector4 result = v;
	return result *= s;
}

Vector4 operator * (float s, const Vector4& v)
{
	return v * s;
}

Vector4 operator / (const Vector4& v1, const Vector4& v2)
{
	Vector4 result = v1;
	return result /= v2;
}

Vector4 operator / (const Vector4& v, float s)
{
	Vector4 result = v;
	return result /= s;
}
