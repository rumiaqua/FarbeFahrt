# pragma once

# include <initializer_list>
# include <algorithm>

namespace Math
{
	/// <summary>弧度法</summary>
	static const double RADIAN = 0.017453292519;

	/// <summary>度数法</summary>
	static const double DEGREE = 57.2957795;

	/// <summary>円周率</summary>
	static const double PI = 3.141592653589;

	/// <summary>π/2</summary>
	static const double HALF_PI = 1.570796326795;

	/// <summary>π/3</summary>
	static const double DIV3_PI = 1.047197551197;

	/// <summary>π/4</summary>
	static const double DIV4_PI = 0.785398163398;

	/// <summary>度数法を弧度法に変換</summary>
	/// <param name="x">度数法</param>
	/// <returns>弧度法</returns>
	double ToRadian(double x);

	/// <summary>弧度法を度数法に変換</summary>
	/// <param name="x">弧度法</param>
	/// <returns>度数法</returns>
	double ToDegree(double x);

	/// <summary>サインを計算</summary>
	/// <param name="x">角度</param>
	/// <returns>サイン</returns>
	double Sin(double x);

	/// <summary>コサインを計算</summary>
	/// <param name="x">角度</param>
	/// <returns>コサイン</returns>
	double Cos(double x);

	/// <summary>タンジェントを計算</summary>
	/// <param name="x">角度</param>
	/// <returns>タンジェント</returns>
	double Tan(double x);

	/// <summary>アークサインを計算</summary>
	/// <param name="x">比率</param>
	/// <returns>アークサイン</returns>
	double Asin(double x);

	/// <summary>アークコサインを計算</summary>
	/// <param name="x">比率</param>
	/// <returns>アークサイン</returns>
	double Acos(double x);

	/// <summary>アークタンジェントを計算</summary>
	/// <param name="x">比率</param>
	/// <returns>アークタンジェント</returns>
	double Atan(double x);

	/// <summary>アークタンジェントを計算</summary>
	/// <param name="y">y成分</param>
	/// <param name="x">x成分</param>
	/// <returns>アークタンジェント</returns>
	double Atan2(double y, double x);

	/// <summary>x以下で最大の整数を返す</summary>
	/// <param name="x">基準値</param>
	/// <returns>x以下で最大の整数</returns>
	double Floor(double x);

	/// <summary>x以上で最大の整数を返す</summary>
	/// <param name="x">基準値</param>
	/// <returns>x以上で最大の整数</returns>
	double Ceiling(double x);

	/// <summary>四捨五入した値を返す</summary>
	/// <param name="x">値</param>
	/// <returns>四捨五入した値</returns>
	double Round(double x);

	/// <summary>符号を返す</summary>
	/// <param name="x">値</param>
	/// <returns>符号</returns>
	double Sign(double x);

	/// <summary>累乗を返す</summary>
	/// <param name="x">値</param>
	/// <param name="x">乗数</param>
	/// <returns>累乗</returns>
	double Pow(double x, double y);

	/// <summary>平方根を返す</summary>
	/// <param name="x">値</param>
	/// <returns>平方根</returns>
	double Sqrt(double x);

	/// <summary>指定桁数でならす</summary>
	/// <param name="x">値</param>
	/// <param name="y">桁数</param>
	/// <returns>ならした値</returns>
	double Smooth(double x, int y);

	/// <summary>0から1の間にクランプする</summary>
	/// <param name="x">値</param>
	/// <returns>0から1の間にクランプされた値</returns>
	double Saturate(double x);

	/// <summary>指定した値の間にクランプする</summary>
	/// <param name="x">値</param>
	/// <param name="y">最小値</param>
	/// <param name="z">最大値</param>
	/// <returns>クランプされた値</returns>
	double Clamp(double x, double y, double z);

	/// <summary>最大の値を返す</summary>
	/// <param name="args">値の初期化リスト</param>
	/// <returns>最大値</returns>
	template <typename Type>
	Type Max(const std::initializer_list<Type>& args)
	{
		return *std::max_element(args.begin(), args.end());
	}

	/// <summary>最小の値を返す</summary>
	/// <param name="args">値の初期化リスト</param>
	/// <returns>最小値</returns>
	template <typename Type>
	Type Min(const std::initializer_list<Type>& args)
	{
		return *std::min_element(args.begin(), args.end());
	}

	/// <summary>値が範囲内にあるかを返す</summary>
	/// <param name="value">値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	template <typename Type>
	bool IsContains(const Type& value, const Type& min, const Type& max)
	{
		return
			min <= value &&
			value <= max;
	}
}
