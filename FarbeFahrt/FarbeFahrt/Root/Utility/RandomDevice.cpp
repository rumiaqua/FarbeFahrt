# include "RandomDevice.hpp"

std::mt19937& RandomDevice::GetInstance()
{
	static std::mt19937 mt{ std::random_device()() };
	return mt;
}

int RandomDevice::Range(int min, int max)
{
	return std::uniform_int_distribution<int>(min, max)(GetInstance());
}

float RandomDevice::Rangef(float min, float max)
{
	return std::uniform_real_distribution<float>(min, max)(GetInstance());
}

float RandomDevice::Normal()
{
	return Rangef(0.0f, 1.0f);
}

bool RandomDevice::Bool(float p)
{
	return std::bernoulli_distribution(p)(GetInstance());
}

size_t RandomDevice::Weight(const std::vector<size_t>& weight)
{
	std::vector<size_t> indices;

	for (size_t i = 0; i < weight.size(); ++i)
	{
		for (size_t j = 0; j < weight[i]; ++j)
		{
			indices.emplace_back(i);
		}
	}

	auto r = (int)std::floor(Normal() * indices.size());

	return indices[r];
}
