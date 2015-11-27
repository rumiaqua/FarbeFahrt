# pragma once

# include "Vector4.h"
# include <DxLib.h>

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Vector3;


/// <summary>�s��</summary>
class Matrix
{
public:

	/// <summary>��s���Ԃ�</summary>
	static const Matrix& zero();

	/// <summary>�P�ʍs���Ԃ�</summary>
	static const Matrix& identity();

public:

	/// <summary>�R���X�g���N�^</summary>
	Matrix();

	/// <summary>�z�񂩂�\�z����</summary>
	explicit Matrix(const float* m);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Matrix(const MATRIX& m);

	/// <summary>������Z�q</summary>
	Matrix& operator = (const Matrix& m);

public:

	/// <summary>�z��ɕϊ�����</summary>
	operator float* ();

	/// <summary>�z��ɕϊ�����</summary>
	operator const float* () const;

	operator MATRIX& ();

	operator const MATRIX& () const;

public:

	/// <summary>�P�ʍs�񂩂ǂ�����Ԃ�</summary>
	bool isIdentity() const;

	/// <summary>��s�񂩂ǂ�����Ԃ�</summary>
	bool isZero() const;

	/// <summary>�t�s�񂪍��邩��Ԃ�</summary>
	bool canInverse() const;

	/// <summary>�t�s�񂩂ǂ�����Ԃ�</summary>
	bool isInverse(const Matrix& matrix) const;

	/// <summary>�s�񎮂�Ԃ�</summary>
	float determinant() const;

	/// <summary>������ɕϊ�����</summary>
	std::string toString() const;

public:

	/// <summary>���s�ړ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	Matrix& Translate(const Vector3& translation);

	/// <summary>��]����</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	Matrix& rotate(const Vector3& axis, double angle);

	/// <summary>�g��k������</summary>
	/// <param name="scaling">�g��k����</param>
	Matrix& scale(const Vector3& scaling);

	/// <summary>�A�t�B���ϊ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	Matrix& transform(const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

	/// <summary>�]�u�s��ɂ���</summary>
	Matrix& transpose();

	/// <summary>�t�s��ɂ���</summary>
	Matrix& inverse();

public:

	/// <summary>���s�ړ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	Matrix translated(const Vector3& translation) const;

	/// <summary>��]�����s���Ԃ�</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	Matrix rotated(const Vector3& axis, double angle) const;

	/// <summary>�g��k�������s���Ԃ�</summary>
	/// <param name="scaling">�g��k����</param>
	Matrix scaled(const Vector3& scaling) const;

	/// <summary>�A�t�B���ϊ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	Matrix transformed(const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling) const;

	/// <summary>�]�u�s���Ԃ�</summary>
	Matrix transposed() const;

	/// <summary>�t�s���Ԃ�</summary>
	Matrix inversed() const;

public:

	Vector4 up() const;

	Vector4 right() const;

	Vector4 forward() const;

public:

	/// <summary>�P�ʍs�񂩂ǂ�����Ԃ�</summary>
	static bool IsIdentity(const Matrix& m);

	/// <summary>��s�񂩂ǂ�����Ԃ�</summary>
	static bool IsZero(const Matrix& m);

	/// <summary>�t�s�񂪍��邩��Ԃ�</summary>
	static bool CanInverse(const Matrix& m);

	/// <summary>�t�s�񂩂ǂ�����Ԃ�</summary>
	static bool IsInverse(const Matrix& m1, const Matrix& m2);

	/// <summary>�s�񎮂�Ԃ�</summary>
	static float Determinant(const Matrix& m);

	/// <summary>������ɕϊ�����</summary>
	static std::string ToString(const Matrix& m);

public:

	/// <summary>���s�ړ��s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	static Matrix Translation(const Vector3& translation);

	/// <summary>��]�s���Ԃ�</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	static Matrix Rotation(const Vector3& axis, double angle);

	/// <summary>�g��k���s���Ԃ�</summary>
	/// <param name="scaling">�g��k����</param>
	static Matrix Scaling(const Vector3& scaling);

	/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix Transformation(const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

public:

	/// <summary>���s�ړ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	static Matrix& Translate(Matrix& matrix, const Vector3& translation);

	/// <summary>��]����</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	static Matrix& Rotate(Matrix& matrix, const Vector3& axis, double angle);

	/// <summary>�g��k������</summary>
	/// <param name="scaling">�g��k����</param>
	static Matrix& Scale(Matrix& matrix, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix& Transform(Matrix& matrix, const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

	/// <summary>�]�u�s��ɂ���</summary>
	static Matrix& Transpose(Matrix& matrix);

	/// <summary>�t�s��ɂ���</summary>
	static Matrix& Inverse(Matrix& matrix);

public:

	/// <summary>���s�ړ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	static Matrix Translated(const Matrix& matrix, const Vector3& translation);

	/// <summary>��]�����s���Ԃ�</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	static Matrix Rotated(const Matrix& matrix, const Vector3& axis, double angle);

	/// <summary>�g��k�������s���Ԃ�</summary>
	/// <param name="scaling">�g��k����</param>
	static Matrix Scaled(const Matrix& matrix, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix Transformed(const Matrix& matrix, const Vector3& translation, const Vector3& axis, double angle, const Vector3& scaling);

	/// <summary>�]�u�s���Ԃ�</summary>
	static Matrix Transposed(const Matrix& matrix);

	/// <summary>�t�s���Ԃ�</summary>
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
