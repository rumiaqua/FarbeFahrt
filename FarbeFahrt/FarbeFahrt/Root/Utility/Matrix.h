# pragma once

# include "Vector4.h"
# include <DxLib.h>

// -------------------------------------------------------------------
// ‘O’uéŒ¾
// -------------------------------------------------------------------
class Vector3;


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
	explicit Matrix(const float* m);

	/// <summary>—v‘f‚ğw’è‚µ‚Ä\’z‚·‚é</summary>
	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	/// <summary>ƒRƒs[ƒRƒ“ƒXƒgƒ‰ƒNƒ^</summary>
	Matrix(const MATRIX& m);

	/// <summary>‘ã“ü‰‰Zq</summary>
	Matrix& operator = (const Matrix& m);

public:

	/// <summary>”z—ñ‚É•ÏŠ·‚·‚é</summary>
	operator float* ();

	/// <summary>”z—ñ‚É•ÏŠ·‚·‚é</summary>
	operator const float* () const;

	operator MATRIX& ();

	operator const MATRIX& () const;

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
	std::string toString() const;

public:

	/// <summary>•½sˆÚ“®‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	Matrix& Translate(const Vector3& translation);

	/// <summary>‰ñ“]‚·‚é</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	Matrix& rotate(const Vector3& axis, double angle);

	/// <summary>Šg‘åk¬‚·‚é</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix& scale(const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix& transform(const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

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
	Matrix rotated(const Vector3& axis, double angle) const;

	/// <summary>Šg‘åk¬‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix scaled(const Vector3& scaling) const;

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	Matrix transformed(const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling) const;

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
	static bool IsIdentity(const Matrix& m);

	/// <summary>—ës—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	static bool IsZero(const Matrix& m);

	/// <summary>‹ts—ñ‚ªì‚ê‚é‚©‚ğ•Ô‚·</summary>
	static bool CanInverse(const Matrix& m);

	/// <summary>‹ts—ñ‚©‚Ç‚¤‚©‚ğ•Ô‚·</summary>
	static bool IsInverse(const Matrix& m1, const Matrix& m2);

	/// <summary>s—ñ®‚ğ•Ô‚·</summary>
	static float Determinant(const Matrix& m);

	/// <summary>•¶š—ñ‚É•ÏŠ·‚·‚é</summary>
	static std::string ToString(const Matrix& m);

public:

	/// <summary>•½sˆÚ“®s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	static Matrix Translation(const Vector3& translation);

	/// <summary>‰ñ“]s—ñ‚ğ•Ô‚·</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	static Matrix Rotation(const Vector3& axis, double angle);

	/// <summary>Šg‘åk¬s—ñ‚ğ•Ô‚·</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix Scaling(const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix Transformation(const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

public:

	/// <summary>•½sˆÚ“®‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	static Matrix& Translate(Matrix& matrix, const Vector3& translation);

	/// <summary>‰ñ“]‚·‚é</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	static Matrix& Rotate(Matrix& matrix, const Vector3& axis, double angle);

	/// <summary>Šg‘åk¬‚·‚é</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix& Scale(Matrix& matrix, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚·‚é</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix& Transform(Matrix& matrix, const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

	/// <summary>“]’us—ñ‚É‚·‚é</summary>
	static Matrix& Transpose(Matrix& matrix);

	/// <summary>‹ts—ñ‚É‚·‚é</summary>
	static Matrix& Inverse(Matrix& matrix);

public:

	/// <summary>•½sˆÚ“®‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	static Matrix Translated(const Matrix& matrix, const Vector3& translation);

	/// <summary>‰ñ“]‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	static Matrix Rotated(const Matrix& matrix, const Vector3& axis, double angle);

	/// <summary>Šg‘åk¬‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix Scaled(const Matrix& matrix, const Vector3& scaling);

	/// <summary>ƒAƒtƒBƒ“•ÏŠ·‚µ‚½s—ñ‚ğ•Ô‚·</summary>
	/// <param name="translation">•½sˆÚ“®—Ê</param>
	/// <param name="axis">‰ñ“]²</param>
	/// <param name="angle">‰ñ“]—Ê</param>
	/// <param name="scaling">Šg‘åk¬—¦</param>
	static Matrix Transformed(const Matrix& matrix, const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

	/// <summary>“]’us—ñ‚ğ•Ô‚·</summary>
	static Matrix Transposed(const Matrix& matrix);

	/// <summary>‹ts—ñ‚ğ•Ô‚·</summary>
	static Matrix Inversed(const Matrix& matrix);

public:

	static Vector4 Up(const Matrix& matrix);

	static Vector4 Right(const Matrix& matrix);

	static Vector4 Forward(const Matrix& matrix);

	static Vector3 Translation(const Matrix& matrix);

	static Matrix Rotation(const Matrix& matrix);

	static Vector3 Scaling(const Matrix& matrix);

public:

	static Matrix LookAt(const Vector3& position, const Vector3& target, const Vector3& up);

	static Matrix Perspective(double fov, float aspect, float nearclip, float farclip);

	static Matrix Viewport(int width, int height);

	static Matrix Lerp(const Matrix& m1, const Matrix& m2, float t);

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
