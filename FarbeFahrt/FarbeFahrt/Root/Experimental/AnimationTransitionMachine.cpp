# include "AnimationTransitionMachine.h"

# include "Utility/String.h"

# include <fstream>

AnimationTransitionMachine::TransitionState::TransitionState()
	: m_transition()
	, m_isAny(false)
{

}

void AnimationTransitionMachine::TransitionState::add(int current, int next)
{
	if (current == -1)
	{
		m_isAny = true;
	}
	m_transition[current] = next;
}

int AnimationTransitionMachine::TransitionState::next(int current) const
{
	return m_isAny ? m_transition.at(-1) : m_transition.at(current);
}

AnimationTransitionMachine::AnimationTransitionMachine(const std::string& name)
	: m_state()
{
	load(name);
}

Optional<int> AnimationTransitionMachine::next(const std::string& identifier, int current) const
{
	if (m_state.find(identifier) == m_state.end())
	{
		return none;
	}
	auto& state = m_state.at(identifier);
	return Optional<int>(state.next(current));
}

void AnimationTransitionMachine::load(const std::string& filename)
{
	std::ifstream ifs { filename };

	if (ifs.bad())
	{
		return;
	}

	m_state.clear();

	std::string line;

	while (std::getline(ifs, line))
	{
		if (line[0] == '#')
		{
			continue;
		}

		auto split = String::Split(line, ',');

		m_state[split[0]].add(
			String::ToValue<int>(split[1]), String::ToValue<int>(split[2]));
	}
}
