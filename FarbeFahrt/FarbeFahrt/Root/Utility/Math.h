# pragma once

# include <cmath>

# include <initializer_list>

# include <algorithm>

namespace DxLib
{
	typedef struct tagVECTOR VECTOR;
	// typedef tagVECTOR VECTOR;
}

namespace Math
{
	/// <summary>�ʓx�@</summary>
	static const float Radian = 0.017453292519f;

	/// <summary>�x���@</summary>
	static const float Degree = 57.295779513082f;

	/// <summary>�~����</summary>
	static const float Pi = 3.141592653589f;

	/// <summary>��/2</summary>
	static const float HalfPi = 1.570796326795f;

	/// <summary>��/3</summary>
	static const float Div3Pi = 1.047197551197f;

	/// <summary>��/4</summary>
	static const float Div4Pi = 0.785398163398f;

	/// <summary>�x���@���ʓx�@�ɕϊ�</summary>
	/// <param name="x">�x���@</param>
	/// <returns>�ʓx�@</returns>
	float ToRadian(float x);

	/// <summary>�ʓx�@��x���@�ɕϊ�</summary>
	/// <param name="x">�ʓx�@</param>
	/// <returns>�x���@</returns>
	float ToDegree(float x);

	/// <summary>�T�C�����v�Z</summary>
	/// <param name="x">�p�x</param>
	/// <returns>�T�C��</returns>
	float Sin(float x);

	/// <summary>�R�T�C�����v�Z</summary>
	/// <param name="x">�p�x</param>
	/// <returns>�R�T�C��</returns>
	float Cos(float x);

	/// <summary>�^���W�F���g���v�Z</summary>
	/// <param name="x">�p�x</param>
	/// <returns>�^���W�F���g</returns>
	float Tan(float x);

	/// <summary>�A�[�N�T�C�����v�Z</summary>
	/// <param name="x">�䗦</param>
	/// <returns>�A�[�N�T�C��</returns>
	float Asin(float x);

	/// <summary>�A�[�N�R�T�C�����v�Z</summary>
	/// <param name="x">�䗦</param>
	/// <returns>�A�[�N�T�C��</returns>
	float Acos(float x);

	/// <summary>�A�[�N�^���W�F���g���v�Z</summary>
	/// <param name="x">�䗦</param>
	/// <returns>�A�[�N�^���W�F���g</returns>
	float Atan(float x);

	/// <summary>�A�[�N�^���W�F���g���v�Z</summary>
	/// <param name="y">y����</param>
	/// <param name="x">x����</param>
	/// <returns>�A�[�N�^���W�F���g</returns>
	float Atan2(float y, float x);

	/// <summary>x�ȉ��ōő�̐�����Ԃ�</summary>
	/// <param name="x">��l</param>
	/// <returns>x�ȉ��ōő�̐���</returns>
	float Floor(float x);

	/// <summary>x�ȏ�ōő�̐�����Ԃ�</summary>
	/// <param name="x">��l</param>
	/// <returns>x�ȏ�ōő�̐���</returns>
	float Ceiling(float x);

	/// <summary>�l�̌ܓ������l��Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <returns>�l�̌ܓ������l</returns>
	float Round(float x);

	/// <summary>������Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <returns>����</returns>
	float Sign(float x);

	/// <summary>�ݏ��Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <param name="x">�搔</param>
	/// <returns>�ݏ�</returns>
	float Pow(float x, float y);

	/// <summary>��������Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <returns>������</returns>
	float Sqrt(float x);

	/// <summary>�w�肵���l�̊ԂɃN�����v����</summary>
	/// <param name="x">�l</param>
	/// <param name="y">�ŏ��l</param>
	/// <param name="z">�ő�l</param>
	/// <returns>�N�����v���ꂽ�l</returns>
	float Clamp(float x, float y, float z);

	/// <summary>�w�茅���łȂ炷</summary>
	/// <param name="x">�l</param>
	/// <param name="y">����</param>
	/// <returns>�Ȃ炵���l</returns>
	float Smooth(float x, int y);

	/// <summary>0����1�̊ԂɃN�����v����</summary>
	/// <param name="x">�l</param>
	/// <returns>0����1�̊ԂɃN�����v���ꂽ�l</returns>
	float Saturate(float x);

	/// <summary>�ő�̒l��Ԃ�</summary>
	/// <param name="args">�l�̏��������X�g</param>
	/// <returns>�ő�l</returns>
	template <typename Type>
	Type Max(std::initializer_list<Type> args)
	{
		return *std::max_element(args.begin(), args.end());
	}

	/// <summary>�ŏ��̒l��Ԃ�</summary>
	/// <param name="args">�l�̏��������X�g</param>
	/// <returns>�ŏ��l</returns>
	template <typename Type>
	Type Min(std::initializer_list<Type> args)
	{
		return *std::min_element(args.begin(), args.end());
	}

	/// <summary>�x�N�g���̂Ȃ��p��Ԃ�</summary>
	/// <param name="from">�n�x�N�g��</param>
	/// <param name="to">�I�x�N�g��</param>
	float Angle(const DxLib::VECTOR& from, const DxLib::VECTOR& to);

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float LengthSquared(const DxLib::VECTOR& v);
}
