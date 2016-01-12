# pragma once

# include <string>
# include <unordered_map>

class AnimationTransitionMachine
{
public:

	class TransitionState
	{
	public:

		TransitionState();

	public:

		void add(int current, int next);
		int next(int current) const;

	private:

		std::unordered_map<int, int> m_transition;
		bool m_isAny;
	};

public:

	AnimationTransitionMachine(const std::string& name);

public:

	int next(const std::string& identifier, int current) const;

private:

	void load(const std::string& filename);

private:

	std::unordered_map<std::string, TransitionState> m_state;
};
