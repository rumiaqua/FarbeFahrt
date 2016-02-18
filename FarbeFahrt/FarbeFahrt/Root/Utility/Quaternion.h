# pragma once

# include "Vector4.h"
# include "Matrix.h"

namespace Utility
{
	// -------------------------------------------------------------------
	// 前置宣言
	// -------------------------------------------------------------------

	class Quaternion
	{
		// ---------------------------------------------------------------
		// システム
		// ---------------------------------------------------------------

	public:

		Quaternion();

		Quaternion(Quaternion const& q);

		Quaternion(float x, float y, float z, float w);

		// ---------------------------------------------------------------
		// 定数
		// ---------------------------------------------------------------

	public:

		/// <summary>単位クォータニオンを返す</summary>
		static Quaternion& Identity();

		// ---------------------------------------------------------------
		// 変換する
		// ---------------------------------------------------------------

	public:

		/// <summary>任意軸回転を行なう</summary>
		Quaternion& Rotate(Vector3 const& axis, float angle);

		/// <summary>ロール回転を行なう</summary>
		Quaternion& Roll(float angle);

		/// <summary>ピッチ回転を行なう</summary>
		Quaternion& Pitch(float angle);

		/// <summary>ヨー回転を行なう</summary>
		Quaternion& Yaw(float angle);

		/// <summary>行列に変換する</summary>
		Matrix ToMatrix();

		// ---------------------------------------------------------------
		// 変換クォータニオンを返す
		// ---------------------------------------------------------------

	public:

		/// <summary>任意軸回転クォータニオンを返す</summary>
		static Quaternion Rotation(Vector3 const& axis, float angle);

		/// <summary>行列に変換する</summary>
		static Matrix ToMatrix(Quaternion const& q);

		/// <summary>共役クォータニオンを返す</summary>
		static Quaternion Conjugate(Quaternion const& q);

	public:

		float x, y, z, w;
	};

	// ---------------------------------------------------------------
	// 演算子オーバーロード
	// ---------------------------------------------------------------

	Quaternion operator * (Quaternion const& q1, Quaternion const& q2);
	Quaternion& operator *= (Quaternion& q1, Quaternion const& q2);
	Vector3 operator * (Vector3 const& v, Quaternion const& q);
	Vector3& operator *= (Vector3 & v, Quaternion const& q);
}
