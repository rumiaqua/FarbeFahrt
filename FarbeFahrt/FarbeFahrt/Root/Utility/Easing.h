# pragma once

# include <functional>

namespace Utility
{
	namespace Easing
	{
		template <float easing(float)>
		class Ease
		{
		public:

			static float In(float t)
			{
				return easing(t);
			}

			static float Out(float t)
			{
				return 1.0f - In(1.0f - t);
			}

			static float InOut(float t)
			{
				return t < 0.5f ?
					In(2.0f * t) / 2.0f :
					0.5f + Out(2.0f * t - 1.0f) / 2.0f;
			}
		};

		float Quad(float t);
		float Cubic(float t);
		float Quart(float t);
		float Quint(float t);
		float Sine(float t);
		float Exp(float t);
		float Circ(float t);
		float Back(float t);
		float Bounce(float t);
		float Elastic(float t);
		float Linear(float t);

		using EaseQuad = Ease<Quad>;
		using EaseCubic = Ease<Cubic>;
		using EaseQuart = Ease<Quart>;
		using EaseQuint = Ease<Quint>;
		using EaseSine = Ease<Sine>;
		using EaseExp = Ease<Exp>;
		using EaseCirc = Ease<Circ>;
		using EaseBack = Ease<Back>;
		using EaseBounce = Ease<Bounce>;
		using EaseElastic = Ease<Elastic>;
		using EaseLinear = Ease<Linear>;
	}
}
