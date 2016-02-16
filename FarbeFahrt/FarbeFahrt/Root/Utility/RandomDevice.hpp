# pragma once

# include <algorithm>

# include <functional>

# include <random>

# include <iostream>

class RandomDevice
{
public:

	/// <summary>���������C���X�^���X��Ԃ�</summary>
	static std::mt19937& GetInstance();

	/// <summary>(min, max]�̗�����Ԃ�</summary>
	/// <param name="min">��I�ŏ��l</param>
	/// <param name="max">�r���I�ő�l</param>
	static int Range(int min, int max);

	/// <summary>(min, max]�̗�����Ԃ�</summary>
	/// <param name="min">��I�ŏ��l</param>
	/// <param name="max">�r���I�ő�l</param>
	static float Rangef(float min, float max);

	/// <summary>0.0����1.0�܂ł̗�����Ԃ�</summary>
	static float Normal();

	/// <summary>p�̊m����true��Ԃ�</summary>
	/// <param name="p">true��Ԃ��m��(0.0 ~ 1.0)</param>
	static bool Bool(float p);

	/// <summary>�d�݂��l�������C���f�b�N�X��Ԃ�</summary>
	/// <param name="weight">�d��</param>
	static size_t Weight(const std::vector<size_t>& weight);
};
