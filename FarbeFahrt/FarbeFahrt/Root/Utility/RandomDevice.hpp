# pragma once

# include <algorithm>

# include <functional>

# include <random>

# include <iostream>

class RandomDevice
{
public:

	/// <summary>乱数生成インスタンスを返す</summary>
	static std::mt19937& GetInstance();

	/// <summary>(min, max]の乱数を返す</summary>
	/// <param name="min">包括的最小値</param>
	/// <param name="max">排他的最大値</param>
	static int Range(int min, int max);

	/// <summary>(min, max]の乱数を返す</summary>
	/// <param name="min">包括的最小値</param>
	/// <param name="max">排他的最大値</param>
	static float Rangef(float min, float max);

	/// <summary>0.0から1.0までの乱数を返す</summary>
	static float Normal();

	/// <summary>pの確率でtrueを返す</summary>
	/// <param name="p">trueを返す確率(0.0 ~ 1.0)</param>
	static bool Bool(float p);

	/// <summary>重みを考慮したインデックスを返す</summary>
	/// <param name="weight">重み</param>
	static size_t Weight(const std::vector<size_t>& weight);
};
