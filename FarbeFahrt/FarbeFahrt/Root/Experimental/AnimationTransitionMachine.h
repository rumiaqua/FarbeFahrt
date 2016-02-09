# pragma once

# include "Utility/Optional.h"

# include <string>
# include <unordered_map>

class AnimationTransitionMachine
{
public:

	struct AnimateState
	{
	public:

		AnimateState();

	public:

		int handle;
		bool isReversed;
	};

	class TransitionState
	{
	public:

		TransitionState();

	public:

		void add(int current, int next, bool isReversed);
		const AnimateState& next(int current) const;

	private:

		std::unordered_map<int, AnimateState> m_transition;
		bool m_isAny;
	};

public:

	AnimationTransitionMachine(const std::string& name);

public:

	Optional<AnimateState> next(const std::string& identifier, int current) const;

private:

	void load(const std::string& filename);

private:

	std::unordered_map<std::string, TransitionState> m_state;
};
