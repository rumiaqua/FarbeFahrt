# pragma once

# include <initializer_list>
# include <algorithm>

namespace Math
{
	/// <summary>�ʓx�@</summary>
	static const double RADIAN = 0.017453292519;

	/// <summary>�x���@</summary>
	static const double DEGREE = 57.2957795;

	/// <summary>�~����</summary>
	static const double PI = 3.141592653589;

	/// <summary>��/2</summary>
	static const double HALF_PI = 1.570796326795;

	/// <summary>��/3</summary>
	static const double DIV3_PI = 1.047197551197;

	/// <summary>��/4</summary>
	static const double DIV4_PI = 0.785398163398;

	/// <summary>�x���@���ʓx�@�ɕϊ�</summary>
	/// <param name="x">�x���@</param>
	/// <returns>�ʓx�@</returns>
	double ToRadian(double x);

	/// <summary>�ʓx�@��x���@�ɕϊ�</summary>
	/// <param name="x">�ʓx�@</param>
	/// <returns>�x���@</returns>
	double ToDegree(double x);

	/// <summary>�T�C�����v�Z</summary>
	/// <param name="x">�p�x</param>
	/// <returns>�T�C��</returns>
	double Sin(double x);

	/// <summary>�R�T�C�����v�Z</summary>
	/// <param name="x">�p�x</param>
	/// <returns>�R�T�C��</returns>
	double Cos(double x);

	/// <summary>�^���W�F���g���v�Z</summary>
	/// <param name="x">�p�x</param>
	/// <returns>�^���W�F���g</returns>
	double Tan(double x);

	/// <summary>�A�[�N�T�C�����v�Z</summary>
	/// <param name="x">�䗦</param>
	/// <returns>�A�[�N�T�C��</returns>
	double Asin(double x);

	/// <summary>�A�[�N�R�T�C�����v�Z</summary>
	/// <param name="x">�䗦</param>
	/// <returns>�A�[�N�T�C��</returns>
	double Acos(double x);

	/// <summary>�A�[�N�^���W�F���g���v�Z</summary>
	/// <param name="x">�䗦</param>
	/// <returns>�A�[�N�^���W�F���g</returns>
	double Atan(double x);

	/// <summary>�A�[�N�^���W�F���g���v�Z</summary>
	/// <param name="y">y����</param>
	/// <param name="x">x����</param>
	/// <returns>�A�[�N�^���W�F���g</returns>
	double Atan2(double y, double x);

	/// <summary>x�ȉ��ōő�̐�����Ԃ�</summary>
	/// <param name="x">��l</param>
	/// <returns>x�ȉ��ōő�̐���</returns>
	double Floor(double x);

	/// <summary>x�ȏ�ōő�̐�����Ԃ�</summary>
	/// <param name="x">��l</param>
	/// <returns>x�ȏ�ōő�̐���</returns>
	double Ceiling(double x);

	/// <summary>�l�̌ܓ������l��Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <returns>�l�̌ܓ������l</returns>
	double Round(double x);

	/// <summary>������Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <returns>����</returns>
	double Sign(double x);

	/// <summary>�ݏ��Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <param name="x">�搔</param>
	/// <returns>�ݏ�</returns>
	double Pow(double x, double y);

	/// <summary>��������Ԃ�</summary>
	/// <param name="x">�l</param>
	/// <returns>������</returns>
	double Sqrt(double x);

	/// <summary>�w�茅���łȂ炷</summary>
	/// <param name="x">�l</param>
	/// <param name="y">����</param>
	/// <returns>�Ȃ炵���l</returns>
	double Smooth(double x, int y);

	/// <summary>0����1�̊ԂɃN�����v����</summary>
	/// <param name="x">�l</param>
	/// <returns>0����1�̊ԂɃN�����v���ꂽ�l</returns>
	double Saturate(double x);

	/// <summary>�w�肵���l�̊ԂɃN�����v����</summary>
	/// <param name="x">�l</param>
	/// <param name="y">�ŏ��l</param>
	/// <param name="z">�ő�l</param>
	/// <returns>�N�����v���ꂽ�l</returns>
	double Clamp(double x, double y, double z);

	/// <summary>�ő�̒l��Ԃ�</summary>
	/// <param name="args">�l�̏��������X�g</param>
	/// <returns>�ő�l</returns>
	template <typename Type>
	Type Max(const std::initializer_list<Type>& args)
	{
		return *std::max_element(args.begin(), args.end());
	}

	/// <summary>�ŏ��̒l��Ԃ�</summary>
	/// <param name="args">�l�̏��������X�g</param>
	/// <returns>�ŏ��l</returns>
	template <typename Type>
	Type Min(const std::initializer_list<Type>& args)
	{
		return *std::min_element(args.begin(), args.end());
	}

	/// <summary>�l���͈͓��ɂ��邩��Ԃ�</summary>
	/// <param name="value">�l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	template <typename Type>
	bool IsContains(const Type& value, const Type& min, const Type& max)
	{
		return
			min <= value &&
			value <= max;
	}
}
