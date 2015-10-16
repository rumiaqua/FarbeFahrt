# pragma once

# include "Vector4.h"

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Vector3;
class String;

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
	Matrix(const float* m);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Matrix(const Matrix& m);

	/// <summary>������Z�q</summary>
	Matrix& operator = (const Matrix& m);

public:

	/// <summary>�z��ɕϊ�����</summary>
	operator float* ();

	/// <summary>�z��ɕϊ�����</summary>
	operator const float* () const;

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
	String toString() const;

public:

	/// <summary>���s�ړ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	Matrix& translate(const Vector3& translation);

	/// <summary>��]����</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	Matrix& rotate(const Vector3& axis, float angle);

	/// <summary>��]����</summary>
	/// <param name="rotation">��]���Ɖ�]��</param>
	Matrix& rotate(const Vector4& rotation);

	/// <summary>�g��k������</summary>
	/// <param name="scaling">�g��k����</param>
	Matrix& scale(const Vector3& scaling);

	/// <summary>�A�t�B���ϊ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	Matrix& transform(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="rotation">��]���Ɖ�]��</param>
	/// <param name="scaling">�g��k����</param>
	Matrix& transform(const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

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
	Matrix rotated(const Vector3& axis, float angle) const;

	/// <summary>��]�����s���Ԃ�</summary>
	/// <param name="rotation">��]���Ɖ�]��</param>
	Matrix rotated(const Vector4& rotation) const;

	/// <summary>�g��k�������s���Ԃ�</summary>
	/// <param name="scaling">�g��k����</param>
	Matrix scaled(const Vector3& scaling) const;

	/// <summary>�A�t�B���ϊ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	Matrix transformed(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling) const;

	/// <summary>�A�t�B���ϊ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="rotation">���Ɖ�]��</param>
	/// <param name="scaling">�g��k����</param>
	Matrix transformed(const Vector3& translation, const Vector4& rotation, const Vector3& scaling) const;

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
	static bool isIdentity(const Matrix& m);

	/// <summary>��s�񂩂ǂ�����Ԃ�</summary>
	static bool isZero(const Matrix& m);

	/// <summary>�t�s�񂪍��邩��Ԃ�</summary>
	static bool canInverse(const Matrix& m);

	/// <summary>�t�s�񂩂ǂ�����Ԃ�</summary>
	static bool isInverse(const Matrix& m1, const Matrix& m2);

	/// <summary>�s�񎮂�Ԃ�</summary>
	static float determinant(const Matrix& m);

	/// <summary>������ɕϊ�����</summary>
	static String toString(const Matrix& m);

public:

	/// <summary>���s�ړ��s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	static Matrix translation(const Vector3& translation);

	/// <summary>��]�s���Ԃ�</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	static Matrix rotation(const Vector3& axis, float angle);

	/// <summary>��]�s���Ԃ�</summary>
	/// <param name="rotation">��]���Ɖ�]��</param>
	static Matrix rotation(const Vector4& rotation);

	/// <summary>�g��k���s���Ԃ�</summary>
	/// <param name="scaling">�g��k����</param>
	static Matrix scaling(const Vector3& scaling);

	/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix transformation(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ��s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="rotation">��]���Ɖ�]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix transformation(const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

public:

	/// <summary>���s�ړ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	static Matrix& translate(Matrix& matrix, const Vector3& translation);

	/// <summary>��]����</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	static Matrix& rotate(Matrix& matrix, const Vector3& axis, float angle);

	/// <summary>��]����</summary>
	/// <param name="rotation">��]���Ɖ�]��</param>
	static Matrix& rotate(Matrix& matrix, const Vector4& rotation);

	/// <summary>�g��k������</summary>
	/// <param name="scaling">�g��k����</param>
	static Matrix& scale(Matrix& matrix, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix& transform(Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ�����</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="rotation">��]���Ɖ�]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix& transform(Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>�]�u�s��ɂ���</summary>
	static Matrix& transpose(Matrix& matrix);

	/// <summary>�t�s��ɂ���</summary>
	static Matrix& inverse(Matrix& matrix);

public:

	/// <summary>���s�ړ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	static Matrix translated(const Matrix& matrix, const Vector3& translation);

	/// <summary>��]�����s���Ԃ�</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	static Matrix rotated(const Matrix& matrix, const Vector3& axis, float angle);

	/// <summary>��]�����s���Ԃ�</summary>
	/// <param name="rotation">��]���Ɖ�]��</param>
	static Matrix rotated(const Matrix& matrix, const Vector4& rotation);

	/// <summary>�g��k�������s���Ԃ�</summary>
	/// <param name="scaling">�g��k����</param>
	static Matrix scaled(const Matrix& matrix, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix transformed(const Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling);

	/// <summary>�A�t�B���ϊ������s���Ԃ�</summary>
	/// <param name="translation">���s�ړ���</param>
	/// <param name="rotation">��]���Ɖ�]��</param>
	/// <param name="scaling">�g��k����</param>
	static Matrix transformed(const Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling);

	/// <summary>�]�u�s���Ԃ�</summary>
	static Matrix transposed(const Matrix& matrix);

	/// <summary>�t�s���Ԃ�</summary>
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
