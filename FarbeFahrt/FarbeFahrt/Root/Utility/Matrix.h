# pragma once

# include "Vector4.h"

// -------------------------------------------------------------------
// ‘O’uéŒ¾
// -------------------------------------------------------------------
class Vector3;
class String;

/// <summary>s—ñ</summary>
class Matrix
{
public:

	/// <summary>—ës—ñ‚ğ•Ô‚·</summary>
	static const Matrix& zero();

	/// <summary>’PˆÊs—ñ‚ğ•Ô‚·</summary>
	static const Matrix& identity();

public:

	/// <summary>ƒRƒ“ƒXƒgƒ‰ƒNƒ^</summary>
	Matrix();

	/// <summary>”z—ñ‚©‚ç\’z‚·‚é</summary>
	Matrix(const float* m);

	/// <summary>—v‘f‚ğw’è‚µ‚Ä\’z‚·‚é</summary>
	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	/// <summary>ƒRƒs[ƒRƒ“ƒXƒgƒ‰ƒNƒ^</summary>
	Matrix(const Matrix& m);

	/// <summary>‘ã“ü‰‰Zq</summary>
	Matrix& operator = (const Matrix& m);

public:

	/// <summary>”z—ñ‚É•ÏŠ·‚·‚é</summary>
	operator float* ();

	/// <summary>”z—ñ‚É•ÏŠ·‚·‚é</summary>
	operator const float* () const;

public:

	/// <summary>’PˆÊs—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	bool isIdentity() const;

	/// <summary>—ës—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	bool isZero() const;

	/// <summary>‹ts—ñ‚ªì‚ê‚é‚©‚ğ•Ô‚·</summary>
	bool canInverse() const;

	/// <summary>‹ts—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	bool isInverse(const Matrix& matrix) const;

	/// <summary>s—ñ®‚ğ•Ô‚·</summary>
	float determinant() const;

	/// <summary>•¶š—ñ‚É•ÏŠ·‚·‚é</summary>
	String toString() const;

public:

	/// <summary>•½sˆÚ“®‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	Matrix& translate(const Vector3& translation);

	/// <summary>‰ñ“]‚·‚é</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	Matrix& rotate(const Vector3& axis, float angle);

	/// <summary>‰ñ“]‚·‚é</summary>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	Matrix& rotate(const Vector4& rotation);

	/// <summary>Šg‘åk¬‚·‚é</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix& scale(const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix& transform(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix& transform(const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>“]’us—ñ‚É‚·‚é</summary>
	Matrix& transpose();

	/// <summary>‹ts—ñ‚É‚·‚é</summary>
	Matrix& inverse();

public:

	/// <summary>•½sˆÚ“®‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	Matrix translated(const Vector3& translation) const;

	/// <summary>‰ñ“]‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	Matrix rotated(const Vector3& axis, float angle) const;

	/// <summary>‰ñ“]‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	Matrix rotated(const Vector4& rotation) const;

	/// <summary>Šg‘åk¬‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix scaled(const Vector3& scaling) const;

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix transformed(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling) const;

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="rotation">²‚Æ‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix transformed(const Vector3& translation, const Vector4& rotation, const Vector3& scaling) const;

	/// <summary>“]’us—ñ‚ğ•Ô‚·</summary>
	Matrix transposed() const;

	/// <summary>‹ts—ñ‚ğ•Ô‚·</summary>
	Matrix inversed() const;

public:

	Vector4 up() const;

	Vector4 right() const;

	Vector4 forward() const;

public:

	/// <summary>’PˆÊs—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	static bool isIdentity(const Matrix& m);

	/// <summary>—ës—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	static bool isZero(const Matrix& m);

	/// <summary>‹ts—ñ‚ªì‚ê‚é‚©‚ğ•Ô‚·</summary>
	static bool canInverse(const Matrix& m);

	/// <summary>‹ts—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	static bool isInverse(const Matrix& m1, const Matrix& m2);

	/// <summary>s—ñ®‚ğ•Ô‚·</summary>
	static float determinant(const Matrix& m);

	/// <summary>•¶š—ñ‚É•ÏŠ·‚·‚é</summary>
	static String toString(const Matrix& m);

public:

	/// <summary>•½sˆÚ“®s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	static Matrix translation(const Vector3& translation);

	/// <summary>‰ñ“]s—ñ‚ğ•Ô‚·</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	static Matrix rotation(const Vector3& axis, float angle);

	/// <summary>‰ñ“]s—ñ‚ğ•Ô‚·</summary>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	static Matrix rotation(const Vector4& rotation);

	/// <summary>Šg‘åk¬s—ñ‚ğ•Ô‚·</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix scaling(const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix transformation(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix transformation(const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

public:

	/// <summary>•½sˆÚ“®‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	static Matrix& translate(Matrix& matrix, const Vector3& translation);

	/// <summary>‰ñ“]‚·‚é</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	static Matrix& rotate(Matrix& matrix, const Vector3& axis, float angle);

	/// <summary>‰ñ“]‚·‚é</summary>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	static Matrix& rotate(Matrix& matrix, const Vector4& rotation);

	/// <summary>Šg‘åk¬‚·‚é</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix& scale(Matrix& matrix, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix& transform(Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix& transform(Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>“]’us—ñ‚É‚·‚é</summary>
	static Matrix& transpose(Matrix& matrix);

	/// <summary>‹ts—ñ‚É‚·‚é</summary>
	static Matrix& inverse(Matrix& matrix);

public:

	/// <summary>•½sˆÚ“®‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	static Matrix translated(const Matrix& matrix, const Vector3& translation);

	/// <summary>‰ñ“]‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	static Matrix rotated(const Matrix& matrix, const Vector3& axis, float angle);

	/// <summary>‰ñ“]‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	static Matrix rotated(const Matrix& matrix, const Vector4& rotation);

	/// <summary>Šg‘åk¬‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix scaled(const Matrix& matrix, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix transformed(const Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="rotation">‰ñ“]²‚Æ‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix transformed(const Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>“]’us—ñ‚ğ•Ô‚·</summary>
	static Matrix transposed(const Matrix& matrix);

	/// <summary>‹ts—ñ‚ğ•Ô‚·</summary>
	static Matrix inversed(const Matrix& matrix);

public:

	static Vector4 up(const Matrix& matrix);

	static Vector4 right(const Matrix& matrix);

	static Vector4 forward(const Matrix& matrix);

public:

	static Matrix lookAt(const Vector3& position, const Vector3& target, const Vector3& up);

	static Matrix perspective(float fov, float aspect, float nearclip, float farclip);

	static Matrix viewport(int width, int height);

public:

	union
	{
		float elm[16];

		float mat[4][4];

		struct
		{
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
		};
	};
};

bool operator == (const Matrix& m1, const Matrix& m2);

bool operator != (const Matrix& m1, const Matrix& m2);

Matrix operator * (const Matrix& m1, const Matrix& m2);

Vector3 operator * (const Vector3& v, const Matrix& m);

Vector4 operator * (const Vector4& v, const Matrix& m);

Matrix& operator *= (Matrix& m1, const Matrix& m2);

Vector3& operator *= (Vector3& v, const Matrix& m);

Vector4& operator *= (Vector4& v, const Matrix& m);
