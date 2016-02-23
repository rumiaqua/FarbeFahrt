# include "Easing.h"
# include "Math.h"

namespace Utility
{
	namespace Easing
	{
		float Quad(float t)
		{
			return t * t;
		}

		float Cubic(float t)
		{
			return t * t * t;
		}

		float Quart(float t)
		{
			return t * t * t * t;
		}

		float Quint(float t)
		{
			return t * t * t * t * t;
		}

		float Sine(float t)
		{
			return 1.0f - (float)Math::Cos(Math::HALF_PI * t);
		}

		float Exp(float t)
		{
			return t == 0.0f ?
				0.0f :
				(float)Math::Pow(2.0, 10.0 * (t - 1.0));
		}

		float Circ(float t)
		{
			t -= 1.0f;
			return 1.0f - (float)Math::Sqrt(1.0f - t * t);
		}

		float Back(float t)
		{
			return t * t * (2.70158f * t - 1.70158f);
		}

		float Bounce(float t)
		{
			if (t < 1.0f / 2.75f)
			{
				return 7.5625f * t * t;
			}
			if (t < 2.0f / 2.75f)
			{
				t -= 1.5f / 2.75f;
				return 7.5625f * t * t + 0.75f;
			}
			if (t < 2.5f / 2.75f)
			{
				t -= 2.25f / 2.75f;
				return 7.5625f * t * t + 0.9375f;
			}
			t -= 2.625f / 2.75f;
			return 7.5625f * t * t + 0.984375f;
		}

		float Elastic(float t)
		{
			if (t == 0.0f)
			{
				return 0.0f;
			}

			if (t == 1.0f)
			{
				return 1.0f;
			}

			float s = 0.04774648292756859813f * (float)Math::Asin(1.0);

			t -= 1.0f;
			return (float)(-Math::Pow(2.0f, 10.0f * t) * Math::Sin((t - s) * 20.94395102393195529f));
		}

		float Linear(float t)
		{
			return t;
		}
	}
}
