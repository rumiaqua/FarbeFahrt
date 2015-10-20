# include "Matrix.h"
# include "String.h"
# include "Vector3.h"
# include "Vector4.h"
# include "Point3.h"
# include "Math.h"
# include "MemoryCast.h"

# include <iostream>

namespace
{
	void Multiply(float* mat, int row, int column, int match, const float* m1, const float* m2)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				for (int k = 0; k < match; ++k)
				{
					double elm0 = mat[i * column + j];
					double elm1 = m1[i * column + k];
					double elm2 = m2[k * column + j];
					double mul = elm0 + elm1 * elm2;
					mat[i * column + j] = (float)mul;
				}
			}
		}
	}
}

const Matrix& Matrix::zero()
{
	static Matrix zero { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	return zero;
}

const Matrix& Matrix::identity()
{
	static Matrix identity { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	return identity;
}

Matrix::Matrix()
	: Matrix(identity())
{

}

Matrix::Matrix(const float* m)
	: Matrix(
		m[0], m[1], m[2], m[3],
		m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11],
		m[12], m[13], m[14], m[15])
{

}

Matrix::Matrix(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44)
	: m11(m11)
	, m12(m12)
	, m13(m13)
	, m14(m14)
	, m21(m21)
	, m22(m22)
	, m23(m23)
	, m24(m24)
	, m31(m31)
	, m32(m32)
	, m33(m33)
	, m34(m34)
	, m41(m41)
	, m42(m42)
	, m43(m43)
	, m44(m44)
{

}

Matrix::Matrix(const Matrix& m)
	: Matrix(m.elm)
{
}

Matrix& Matrix::operator = (const Matrix& m)
{
	this->m11 = m.m11;
	this->m12 = m.m12;
	this->m13 = m.m13;
	this->m14 = m.m14;

	this->m21 = m.m21;
	this->m22 = m.m22;
	this->m23 = m.m23;
	this->m24 = m.m24;

	this->m31 = m.m31;
	this->m32 = m.m32;
	this->m33 = m.m33;
	this->m34 = m.m34;

	this->m41 = m.m41;
	this->m42 = m.m42;
	this->m43 = m.m43;
	this->m44 = m.m44;

	return *this;
}

Matrix::operator float* ()
{
	return elm;
}

Matrix::operator const float* () const
{
	return elm;
}

bool Matrix::isIdentity() const
{
	return isIdentity(*this);
}

bool Matrix::isZero() const
{
	return isZero(*this);
}

bool Matrix::canInverse() const
{
	return canInverse(*this);
}

bool Matrix::isInverse(const Matrix& matrix) const
{
	return isInverse(*this, matrix);
}

float Matrix::determinant() const
{
	return determinant(*this);
}

String Matrix::toString() const
{
	return toString(*this);
}

Matrix& Matrix::translate(const Vector3& translation)
{
	return translate(*this, translation);
}

Matrix& Matrix::rotate(const Vector3& axis, float angle)
{
	return rotate(*this, axis, angle);
}

Matrix& Matrix::rotate(const Vector4& rotation)
{
	return rotate(*this, rotation);
}

Matrix& Matrix::scale(const Vector3& scaling)
{
	return scale(*this, scaling);
}

Matrix& Matrix::transform(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling)
{
	return transform(*this, translation, axis, angle, scaling);
}

Matrix& Matrix::transform(const Vector3& translation, const Vector4& rotation, const Vector3& scaling)
{
	return transform(*this, translation, rotation, scaling);
}

Matrix& Matrix::transpose()
{
	return transpose(*this);
}

Matrix& Matrix::inverse()
{
	return inverse(*this);
}

Matrix Matrix::translated(const Vector3& translation) const
{
	return translated(*this, translation);
}

Matrix Matrix::rotated(const Vector3& axis, float angle) const
{
	return rotated(*this, axis, angle);
}

Matrix Matrix::rotated(const Vector4& rotation) const
{
	return rotated(*this, rotation);
}

Matrix Matrix::scaled(const Vector3& scaling) const
{
	return scaled(*this, scaling);
}

Matrix Matrix::transformed(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling) const
{
	return transformed(*this, translation, axis, angle, scaling);
}

Matrix Matrix::transformed(const Vector3& translation, const Vector4& rotation, const Vector3& scaling) const
{
	return transformed(*this, translation, rotation, scaling);
}

Matrix Matrix::transposed() const
{
	return transposed(*this);
}

Matrix Matrix::inversed() const
{
	return inversed(*this);
}

Vector4 Matrix::up() const
{
	return up(*this);
}

Vector4 Matrix::right() const
{
	return right(*this);
}

Vector4 Matrix::forward() const
{
	return forward(*this);
}

bool Matrix::isIdentity(const Matrix& m)
{
	return m == identity();
}

bool Matrix::isZero(const Matrix& m)
{
	return m == zero();
}

bool Matrix::canInverse(const Matrix& m)
{
	return determinant(m) != 0.0;
}

bool Matrix::isInverse(const Matrix& m1, const Matrix& m2)
{
	return isIdentity(m1 * m2);
}

float Matrix::determinant(const Matrix& matrix)
{
	double det =
		matrix.mat[0][0] * matrix.mat[1][1] * matrix.mat[2][2] * matrix.mat[3][3] +
		matrix.mat[0][0] * matrix.mat[1][2] * matrix.mat[2][3] * matrix.mat[3][1] +
		matrix.mat[0][0] * matrix.mat[1][3] * matrix.mat[2][1] * matrix.mat[3][2] +
		matrix.mat[0][1] * matrix.mat[1][0] * matrix.mat[2][3] * matrix.mat[3][2] +
		matrix.mat[0][1] * matrix.mat[1][2] * matrix.mat[2][0] * matrix.mat[3][3] +
		matrix.mat[0][1] * matrix.mat[1][3] * matrix.mat[2][2] * matrix.mat[3][0] +
		matrix.mat[0][2] * matrix.mat[1][0] * matrix.mat[2][1] * matrix.mat[3][3] +
		matrix.mat[0][2] * matrix.mat[1][1] * matrix.mat[2][3] * matrix.mat[3][0] +
		matrix.mat[0][2] * matrix.mat[1][3] * matrix.mat[2][0] * matrix.mat[3][1] +
		matrix.mat[0][3] * matrix.mat[1][0] * matrix.mat[2][2] * matrix.mat[3][1] +
		matrix.mat[0][3] * matrix.mat[1][1] * matrix.mat[2][0] * matrix.mat[3][2] +
		matrix.mat[0][3] * matrix.mat[1][2] * matrix.mat[2][1] * matrix.mat[3][0] -
		matrix.mat[0][0] * matrix.mat[1][1] * matrix.mat[2][3] * matrix.mat[3][2] -
		matrix.mat[0][0] * matrix.mat[1][2] * matrix.mat[2][1] * matrix.mat[3][3] -
		matrix.mat[0][0] * matrix.mat[1][3] * matrix.mat[2][2] * matrix.mat[3][1] -
		matrix.mat[0][1] * matrix.mat[1][0] * matrix.mat[2][2] * matrix.mat[3][3] -
		matrix.mat[0][1] * matrix.mat[1][2] * matrix.mat[2][3] * matrix.mat[3][0] -
		matrix.mat[0][1] * matrix.mat[1][3] * matrix.mat[2][0] * matrix.mat[3][2] -
		matrix.mat[0][2] * matrix.mat[1][0] * matrix.mat[2][3] * matrix.mat[3][1] -
		matrix.mat[0][2] * matrix.mat[1][1] * matrix.mat[2][0] * matrix.mat[3][3] -
		matrix.mat[0][2] * matrix.mat[1][3] * matrix.mat[2][1] * matrix.mat[3][0] -
		matrix.mat[0][3] * matrix.mat[1][0] * matrix.mat[2][1] * matrix.mat[3][2] -
		matrix.mat[0][3] * matrix.mat[1][1] * matrix.mat[2][2] * matrix.mat[3][0] -
		matrix.mat[0][3] * matrix.mat[1][2] * matrix.mat[2][0] * matrix.mat[3][1];
	return (float)det;
}

String Matrix::toString(const Matrix& m)
{
	return String::create(
		"f[0] : ", memory_cast<Vector4>(m.mat[0])->toString(), "\n",
		"f[1] : ", memory_cast<Vector4>(m.mat[1])->toString(), "\n",
		"f[2] : ", memory_cast<Vector4>(m.mat[2])->toString(), "\n",
		"f[3] : ", memory_cast<Vector4>(m.mat[3])->toString());
}

Matrix Matrix::translation(const Vector3& translation)
{
	return translated(identity(), translation);
}

Matrix Matrix::rotation(const Vector3& axis, float angle)
{
	return rotated(identity(), axis, angle);
}

Matrix Matrix::rotation(const Vector4& rotation)
{
	return rotated(identity(), rotation);
}

Matrix Matrix::scaling(const Vector3& scaling)
{
	return scaled(identity(), scaling);
}

Matrix Matrix::transformation(const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling)
{
	return transformed(identity(), translation, axis, angle, scaling);
}

Matrix Matrix::transformation(const Vector3& translation, const Vector4& rotation, const Vector3& scaling)
{
	return transformed(identity(), translation, rotation, scaling);
}

Matrix& Matrix::translate(Matrix& matrix, const Vector3& translation)
{
	matrix.m41 += translation.x;
	matrix.m42 += translation.y;
	matrix.m43 += translation.z;
	return matrix;
}

Matrix& Matrix::rotate(Matrix& matrix, const Vector3& axis, float angle)
{
	Vector4 X = Vector4(Vector3(matrix.m11, matrix.m12, matrix.m13).rotate(axis, angle), 0.0f);
	Vector4 Y = Vector4(Vector3(matrix.m21, matrix.m22, matrix.m23).rotate(axis, angle), 0.0f);
	Vector4 Z = Vector4(Vector3(matrix.m31, matrix.m32, matrix.m33).rotate(axis, angle), 0.0f);
	matrix.m11 = X.x; matrix.m12 = X.y; matrix.m13 = X.z;
	matrix.m21 = Y.x; matrix.m22 = Y.y; matrix.m23 = Y.z;
	matrix.m31 = Z.x; matrix.m32 = Z.y; matrix.m33 = Z.z;
	return matrix;
}

Matrix& Matrix::rotate(Matrix& matrix, const Vector4& rotation)
{
	return rotate(matrix, Vector3(rotation), rotation.w);
}

Matrix& Matrix::scale(Matrix& matrix, const Vector3& scaling)
{
	matrix.m11 *= scaling.x; matrix.m12 *= scaling.x; matrix.m13 *= scaling.x;
	matrix.m21 *= scaling.y; matrix.m22 *= scaling.y; matrix.m23 *= scaling.y;
	matrix.m31 *= scaling.z; matrix.m32 *= scaling.z; matrix.m33 *= scaling.z;
	return matrix;
}

Matrix& Matrix::transform(Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling)
{
	return translate(rotate(scale(matrix, scaling), axis, angle), translation);
}

Matrix& Matrix::transform(Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling)
{
	return transform(matrix, translation, Vector3(rotation), rotation.w, scaling);
}

Matrix& Matrix::transpose(Matrix& matrix)
{
	return matrix = transposed(matrix);
}

Matrix& Matrix::inverse(Matrix& matrix)
{
	return matrix = inversed(matrix);
}

Matrix Matrix::translated(const Matrix& matrix, const Vector3& translation)
{
	Matrix m = matrix;
	return translate(m, translation);
}

Matrix Matrix::rotated(const Matrix& matrix, const Vector3& axis, float angle)
{
	Matrix m = matrix;
	return rotate(m, axis, angle);
}

Matrix Matrix::rotated(const Matrix& matrix, const Vector4& rotation)
{
	Matrix m = matrix;
	return rotate(m, Vector3(rotation), rotation.w);
}

Matrix Matrix::scaled(const Matrix& matrix, const Vector3& scaling)
{
	Matrix m = matrix;
	return scale(m, scaling);
}

Matrix Matrix::transformed(const Matrix& matrix, const Vector3& translation, const Vector3& axis, float angle, const Vector3& scaling)
{
	Matrix m = matrix;
	return transform(m, translation, axis, angle, scaling);
}

Matrix Matrix::transformed(const Matrix& matrix, const Vector3& translation, const Vector4& rotation, const Vector3& scaling)
{
	Matrix m = matrix;
	return transform(m, translation, Vector3(rotation), rotation.w, scaling);
}

Matrix Matrix::transposed(const Matrix& matrix)
{
	return Matrix {
		matrix.m11, matrix.m21, matrix.m31, matrix.m41,
		matrix.m12, matrix.m22, matrix.m32, matrix.m42,
		matrix.m13, matrix.m23, matrix.m33, matrix.m43,
		matrix.m14, matrix.m24, matrix.m34, matrix.m44 };
}

Matrix Matrix::inversed(const Matrix& matrix)
{
	float det = determinant(matrix);

	if (det == 0.0f)
	{
		return zero();
	}

	double m11 = (
		matrix.mat[1][1] * matrix.mat[2][2] * matrix.mat[3][3] +
		matrix.mat[1][2] * matrix.mat[2][3] * matrix.mat[3][1] +
		matrix.mat[1][3] * matrix.mat[2][1] * matrix.mat[3][2] -
		matrix.mat[1][1] * matrix.mat[2][3] * matrix.mat[3][2] -
		matrix.mat[1][2] * matrix.mat[2][1] * matrix.mat[3][3] -
		matrix.mat[1][3] * matrix.mat[2][2] * matrix.mat[3][1]) / det;

	double m12 = (
		matrix.mat[0][1] * matrix.mat[2][3] * matrix.mat[3][2] +
		matrix.mat[0][2] * matrix.mat[2][1] * matrix.mat[3][3] +
		matrix.mat[0][3] * matrix.mat[2][2] * matrix.mat[3][1] -
		matrix.mat[0][1] * matrix.mat[2][2] * matrix.mat[3][3] -
		matrix.mat[0][2] * matrix.mat[2][3] * matrix.mat[3][1] -
		matrix.mat[0][3] * matrix.mat[2][1] * matrix.mat[3][2]) / det;

	double m13 = (
		matrix.mat[0][1] * matrix.mat[1][2] * matrix.mat[3][3] +
		matrix.mat[0][2] * matrix.mat[1][3] * matrix.mat[3][1] +
		matrix.mat[0][3] * matrix.mat[1][1] * matrix.mat[3][2] -
		matrix.mat[0][1] * matrix.mat[1][3] * matrix.mat[3][2] -
		matrix.mat[0][2] * matrix.mat[1][1] * matrix.mat[3][3] -
		matrix.mat[0][3] * matrix.mat[1][2] * matrix.mat[3][1]) / det;

	double m14 = (
		matrix.mat[0][1] * matrix.mat[1][3] * matrix.mat[2][2] +
		matrix.mat[0][2] * matrix.mat[1][1] * matrix.mat[2][3] +
		matrix.mat[0][3] * matrix.mat[1][2] * matrix.mat[2][1] -
		matrix.mat[0][1] * matrix.mat[1][2] * matrix.mat[2][3] -
		matrix.mat[0][2] * matrix.mat[1][3] * matrix.mat[2][1] -
		matrix.mat[0][3] * matrix.mat[1][1] * matrix.mat[2][2]) / det;

	double m21 = (
		matrix.mat[1][0] * matrix.mat[2][3] * matrix.mat[3][2] +
		matrix.mat[1][2] * matrix.mat[2][0] * matrix.mat[3][3] +
		matrix.mat[1][3] * matrix.mat[2][2] * matrix.mat[3][0] -
		matrix.mat[1][0] * matrix.mat[2][2] * matrix.mat[3][3] -
		matrix.mat[1][2] * matrix.mat[2][3] * matrix.mat[3][0] -
		matrix.mat[1][3] * matrix.mat[2][0] * matrix.mat[3][2]) / det;

	double m22 = (
		matrix.mat[0][0] * matrix.mat[2][2] * matrix.mat[3][3] +
		matrix.mat[0][2] * matrix.mat[2][3] * matrix.mat[3][0] +
		matrix.mat[0][3] * matrix.mat[2][0] * matrix.mat[3][2] -
		matrix.mat[0][0] * matrix.mat[2][3] * matrix.mat[3][2] -
		matrix.mat[0][2] * matrix.mat[2][0] * matrix.mat[3][3] -
		matrix.mat[0][3] * matrix.mat[2][2] * matrix.mat[3][0]) / det;

	double m23 = (
		matrix.mat[0][0] * matrix.mat[1][3] * matrix.mat[3][2] +
		matrix.mat[0][2] * matrix.mat[1][0] * matrix.mat[3][3] +
		matrix.mat[0][3] * matrix.mat[1][2] * matrix.mat[3][0] -
		matrix.mat[0][0] * matrix.mat[1][2] * matrix.mat[3][3] -
		matrix.mat[0][2] * matrix.mat[1][3] * matrix.mat[3][0] -
		matrix.mat[0][3] * matrix.mat[1][0] * matrix.mat[3][2]) / det;

	double m24 = (
		matrix.mat[0][0] * matrix.mat[1][2] * matrix.mat[2][3] +
		matrix.mat[0][2] * matrix.mat[1][3] * matrix.mat[2][0] +
		matrix.mat[0][3] * matrix.mat[1][0] * matrix.mat[2][2] -
		matrix.mat[0][0] * matrix.mat[1][3] * matrix.mat[2][2] -
		matrix.mat[0][2] * matrix.mat[1][0] * matrix.mat[2][3] -
		matrix.mat[0][3] * matrix.mat[1][2] * matrix.mat[2][0]) / det;

	double m31 = (
		matrix.mat[1][0] * matrix.mat[2][1] * matrix.mat[3][3] +
		matrix.mat[1][1] * matrix.mat[2][3] * matrix.mat[3][0] +
		matrix.mat[1][3] * matrix.mat[2][0] * matrix.mat[3][1] -
		matrix.mat[1][0] * matrix.mat[2][3] * matrix.mat[3][1] -
		matrix.mat[1][1] * matrix.mat[2][0] * matrix.mat[3][3] -
		matrix.mat[1][3] * matrix.mat[2][1] * matrix.mat[3][0]) / det;

	double m32 = (
		matrix.mat[0][0] * matrix.mat[2][3] * matrix.mat[3][1] +
		matrix.mat[0][1] * matrix.mat[2][0] * matrix.mat[3][3] +
		matrix.mat[0][3] * matrix.mat[2][1] * matrix.mat[3][0] -
		matrix.mat[0][0] * matrix.mat[2][1] * matrix.mat[3][3] -
		matrix.mat[0][1] * matrix.mat[2][3] * matrix.mat[3][0] -
		matrix.mat[0][3] * matrix.mat[2][0] * matrix.mat[3][1]) / det;

	double m33 = (
		matrix.mat[0][0] * matrix.mat[1][1] * matrix.mat[3][3] +
		matrix.mat[0][1] * matrix.mat[1][3] * matrix.mat[3][0] +
		matrix.mat[0][3] * matrix.mat[1][0] * matrix.mat[3][1] -
		matrix.mat[0][0] * matrix.mat[1][3] * matrix.mat[3][1] -
		matrix.mat[0][1] * matrix.mat[1][0] * matrix.mat[3][3] -
		matrix.mat[0][3] * matrix.mat[1][1] * matrix.mat[3][0]) / det;

	double m34 = (
		matrix.mat[0][0] * matrix.mat[1][3] * matrix.mat[2][1] +
		matrix.mat[0][1] * matrix.mat[1][0] * matrix.mat[2][3] +
		matrix.mat[0][3] * matrix.mat[1][1] * matrix.mat[2][0] -
		matrix.mat[0][0] * matrix.mat[1][1] * matrix.mat[2][3] -
		matrix.mat[0][1] * matrix.mat[1][3] * matrix.mat[2][0] -
		matrix.mat[0][3] * matrix.mat[1][0] * matrix.mat[2][1]) / det;

	double m41 = (
		matrix.mat[1][0] * matrix.mat[2][2] * matrix.mat[3][1] +
		matrix.mat[1][1] * matrix.mat[2][0] * matrix.mat[3][2] +
		matrix.mat[1][2] * matrix.mat[2][1] * matrix.mat[3][0] -
		matrix.mat[1][0] * matrix.mat[2][1] * matrix.mat[3][2] -
		matrix.mat[1][1] * matrix.mat[2][2] * matrix.mat[3][0] -
		matrix.mat[1][2] * matrix.mat[2][0] * matrix.mat[3][1]) / det;

	double m42 = (
		matrix.mat[0][0] * matrix.mat[2][1] * matrix.mat[3][2] +
		matrix.mat[0][1] * matrix.mat[2][2] * matrix.mat[3][0] +
		matrix.mat[0][2] * matrix.mat[2][0] * matrix.mat[3][1] -
		matrix.mat[0][0] * matrix.mat[2][2] * matrix.mat[3][1] -
		matrix.mat[0][1] * matrix.mat[2][0] * matrix.mat[3][2] -
		matrix.mat[0][2] * matrix.mat[2][1] * matrix.mat[3][0]) / det;

	double m43 = (
		matrix.mat[0][0] * matrix.mat[1][2] * matrix.mat[3][1] +
		matrix.mat[0][1] * matrix.mat[1][0] * matrix.mat[3][2] +
		matrix.mat[0][2] * matrix.mat[1][1] * matrix.mat[3][0] -
		matrix.mat[0][0] * matrix.mat[1][1] * matrix.mat[3][2] -
		matrix.mat[0][1] * matrix.mat[1][2] * matrix.mat[3][0] -
		matrix.mat[0][2] * matrix.mat[1][0] * matrix.mat[3][1]) / det;

	double m44 = (
		matrix.mat[0][0] * matrix.mat[1][1] * matrix.mat[2][2] +
		matrix.mat[0][1] * matrix.mat[1][2] * matrix.mat[2][0] +
		matrix.mat[0][2] * matrix.mat[1][0] * matrix.mat[2][1] -
		matrix.mat[0][0] * matrix.mat[1][2] * matrix.mat[2][1] -
		matrix.mat[0][1] * matrix.mat[1][0] * matrix.mat[2][2] -
		matrix.mat[0][2] * matrix.mat[1][1] * matrix.mat[2][0]) / det;

	return Matrix(
		(float)m11, (float)m12, (float)m13, (float)m14,
		(float)m21, (float)m22, (float)m23, (float)m24,
		(float)m31, (float)m32, (float)m33, (float)m34,
		(float)m41, (float)m42, (float)m43, (float)m44);
}

Vector4 Matrix::up(const Matrix& matrix)
{
	return Vector4(matrix.m21, matrix.m22, matrix.m23, 0.0f);
}

Vector4 Matrix::right(const Matrix & matrix)
{
	return Vector4(matrix.m11, matrix.m12, matrix.m13, 0.0f);
}

Vector4 Matrix::forward(const Matrix & matrix)
{
	return Vector4(matrix.m31, matrix.m32, matrix.m33, 0.0f);
}

Matrix Matrix::lookAt(const Vector3& position, const Vector3& target, const Vector3& up)
{
	Matrix matrix;
	Vector3 Z = Vector3::normalize(target - position);
	Vector3 X = Vector3::normalize(Vector3::cross(up, Z));
	Vector3 Y = Vector3::cross(Z, X);
	matrix.m11 = X.x; matrix.m21 = X.y; matrix.m31 = X.z;
	matrix.m12 = Y.x; matrix.m22 = Y.y; matrix.m32 = Y.z;
	matrix.m13 = Z.x; matrix.m23 = Z.y; matrix.m33 = Z.z;
	Vector3 pos = -position;
	matrix.m41 = Vector3::dot(pos, X);
	matrix.m42 = Vector3::dot(pos, Y);
	matrix.m43 = Vector3::dot(pos, Z);
	return matrix;
}

Matrix Matrix::perspective(float fov, float aspect, float nearclip, float farclip)
{
	double y = 1 / (float)Math::tan(fov / 2.0);
	double x = y / aspect;
	double z = farclip / (farclip - nearclip);
	double w = -z * nearclip;
	return Matrix(
		(float)x, 0, 0, 0,
		0, (float)y, 0, 0,
		0, 0, (float)z, 1,
		0, 0, (float)w, 0);
}

Matrix Matrix::viewport(int width, int height)
{
	float w = width / 2.0f;
	float h = height / 2.0f;
	return Matrix(
		w, 0, 0, 0,
		0, -h, 0, 0,
		0, 0, 1, 0,
		w, h, 0, 1);
}

bool operator == (const Matrix& m1, const Matrix& m2)
{
	for (int i = 0; i < 16; ++i)
	{
		if (m1.elm[i] != m2.elm[i])
		{
			return false;
		}
	}
	return true;
}

bool operator != (const Matrix& m1, const Matrix& m2)
{
	return !(m1 == m2);
}

Matrix operator * (const Matrix& m1, const Matrix& m2)
{
	Matrix m = Matrix::zero();

	Multiply(m, 4, 4, 4, m1, m2);

	return m;
}

Vector3 operator * (const Vector3& v, const Matrix& m)
{
	return Vector3(Vector4(v, 1.0f) * m);
}

Vector4 operator * (const Vector4& v, const Matrix& m)
{
	Vector4 r;

	Multiply(r, 1, 4, 4, v, m);

	return r;
}

Matrix& operator *= (Matrix& m1, const Matrix& m2)
{
	return m1 = m1 * m2;
}

Vector3& operator *= (Vector3& v, const Matrix& m)
{
	return v = v * m;
}

Vector4& operator *= (Vector4& v, const Matrix& m)
{
	return v = v * m;
}
