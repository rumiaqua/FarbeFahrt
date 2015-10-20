# pragma once

# include "Vector4.h"
# include <DxLib.h>

// -------------------------------------------------------------------
// 前置宣言
// -------------------------------------------------------------------
class Vector3;
class String;

/// <summary>行列</summary>
class Matrix
{
public:

	/// <summary>零行列を返す</summary>
	static const Matrix& zero();

	/// <summary>単位行列を返す</summary>
	static const Matrix& identity();

public:

	/// <summary>コンストラクタ</summary>
	Matrix();

	/// <summary>配列から構築する</summary>
	explicit Matrix(const float* m);

	/// <summary>要素を指定して構築する</summary>
	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	/// <summary>コピーコンストラクタ</summary>
	Matrix(const MATRIX& m);

	/// <summary>代入演算子</summary>
	Matrix& operator = (const Matrix& m);

public:

	/// <summary>配列に変換する</summary>
	operator float* ();

	/// <summary>配列に変換する</summary>
	operator const float* () const;

	operator MATRIX& ();

	operator const MATRIX& () const;

public:

	/// <summary>単位行列かどうかを返す</summary>
	bool isIdentity() const;

	/// <summary>零行列かどうかを返す</summary>
	bool isZero() const;

	/// <summary>逆行列が作れるかを返す</summary>
	bool canInverse() const;

	/// <summary>逆行列かどうかを返す</summary>
	bool isInverse(const Matrix& matrix) const;

	/// <summary>行列式を返す</summary>
	float determinant() const;

	/// <summary>文字列に変換する</summary>
	String toString() const;

public:

	/// <summary>平行移動する</summary>
	/// <param name="translation">平行移動量</param>
	Matrix& translate(const Vector3& translation);

	/// <summary>回転する</summary>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	Matrix& rotate(const Vector3& axis, float angle);

	/// <summary>回転する</summary>
	/// <param name="rotation">回転軸と回転量</param>
	Matrix& rotate(const Vector4& rotation);

	/// <summary>拡大縮小する</summary>
	/// <param name="scaling">拡大縮小率</param>
	Matrix& scale(const Vector3& scaling);

	/// <summary>アフィン変換する</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	Matrix& transform(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>アフィン変換する</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="rotation">回転軸と回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	Matrix& transform(const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>転置行列にする</summary>
	Matrix& transpose();

	/// <summary>逆行列にする</summary>
	Matrix& inverse();

public:

	/// <summary>平行移動した行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	Matrix translated(const Vector3& translation) const;

	/// <summary>回転した行列を返す</summary>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	Matrix rotated(const Vector3& axis, float angle) const;

	/// <summary>回転した行列を返す</summary>
	/// <param name="rotation">回転軸と回転量</param>
	Matrix rotated(const Vector4& rotation) const;

	/// <summary>拡大縮小した行列を返す</summary>
	/// <param name="scaling">拡大縮小率</param>
	Matrix scaled(const Vector3& scaling) const;

	/// <summary>アフィン変換した行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	Matrix transformed(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling) const;

	/// <summary>アフィン変換した行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="rotation">軸と回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	Matrix transformed(const Vector3& translation, const Vector4& rotation, const Vector3& scaling) const;

	/// <summary>転置行列を返す</summary>
	Matrix transposed() const;

	/// <summary>逆行列を返す</summary>
	Matrix inversed() const;

public:

	Vector4 up() const;

	Vector4 right() const;

	Vector4 forward() const;

public:

	/// <summary>単位行列かどうかを返す</summary>
	static bool isIdentity(const Matrix& m);

	/// <summary>零行列かどうかを返す</summary>
	static bool isZero(const Matrix& m);

	/// <summary>逆行列が作れるかを返す</summary>
	static bool canInverse(const Matrix& m);

	/// <summary>逆行列かどうかを返す</summary>
	static bool isInverse(const Matrix& m1, const Matrix& m2);

	/// <summary>行列式を返す</summary>
	static float determinant(const Matrix& m);

	/// <summary>文字列に変換する</summary>
	static String toString(const Matrix& m);

public:

	/// <summary>平行移動行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	static Matrix translation(const Vector3& translation);

	/// <summary>回転行列を返す</summary>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	static Matrix rotation(const Vector3& axis, float angle);

	/// <summary>回転行列を返す</summary>
	/// <param name="rotation">回転軸と回転量</param>
	static Matrix rotation(const Vector4& rotation);

	/// <summary>拡大縮小行列を返す</summary>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix scaling(const Vector3& scaling);

	/// <summary>アフィン変換行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix transformation(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>アフィン変換行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="rotation">回転軸と回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix transformation(const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

public:

	/// <summary>平行移動する</summary>
	/// <param name="translation">平行移動量</param>
	static Matrix& translate(Matrix& matrix, const Vector3& translation);

	/// <summary>回転する</summary>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	static Matrix& rotate(Matrix& matrix, const Vector3& axis, float angle);

	/// <summary>回転する</summary>
	/// <param name="rotation">回転軸と回転量</param>
	static Matrix& rotate(Matrix& matrix, const Vector4& rotation);

	/// <summary>拡大縮小する</summary>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix& scale(Matrix& matrix, const Vector3& scaling);

	/// <summary>アフィン変換する</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix& transform(Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>アフィン変換する</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="rotation">回転軸と回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix& transform(Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>転置行列にする</summary>
	static Matrix& transpose(Matrix& matrix);

	/// <summary>逆行列にする</summary>
	static Matrix& inverse(Matrix& matrix);

public:

	/// <summary>平行移動した行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	static Matrix translated(const Matrix& matrix, const Vector3& translation);

	/// <summary>回転した行列を返す</summary>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	static Matrix rotated(const Matrix& matrix, const Vector3& axis, float angle);

	/// <summary>回転した行列を返す</summary>
	/// <param name="rotation">回転軸と回転量</param>
	static Matrix rotated(const Matrix& matrix, const Vector4& rotation);

	/// <summary>拡大縮小した行列を返す</summary>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix scaled(const Matrix& matrix, const Vector3& scaling);

	/// <summary>アフィン変換した行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix transformed(const Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>アフィン変換した行列を返す</summary>
	/// <param name="translation">平行移動量</param>
	/// <param name="rotation">回転軸と回転量</param>
	/// <param name="scaling">拡大縮小率</param>
	static Matrix transformed(const Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>転置行列を返す</summary>
	static Matrix transposed(const Matrix& matrix);

	/// <summary>逆行列を返す</summary>
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
