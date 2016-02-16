# include "AnimationTransitionMachine.h"

# include "Utility/String.h"

# include <fstream>

AnimationTransitionMachine::AnimateState::AnimateState()
	: handle(-1)
	, isReversed(false)
{
	
}

AnimationTransitionMachine::TransitionState::TransitionState()
	: m_transition()
	, m_isAny(false)
{

}

void AnimationTransitionMachine::TransitionState::add(int current, int next, bool isReversed)
{
	if (current == -1)
	{
		m_isAny = true;
	}
	m_transition[current].handle = next;
	m_transition[current].isReversed = isReversed;
}

const AnimationTransitionMachine::AnimateState& AnimationTransitionMachine::TransitionState::next(int current) const
{
	return m_isAny ? m_transition.at(-1) : m_transition.at(current);
}

bool AnimationTransitionMachine::TransitionState::isExist(int current) const
{
	return m_isAny || m_transition.find(current) != m_transition.end();
}

AnimationTransitionMachine::AnimationTransitionMachine(const std::string& name)
	: m_state()
{
	load(name);
}

Optional<AnimationTransitionMachine::AnimateState> AnimationTransitionMachine::next(const std::string& identifier, int current) const
{
	if (m_state.find(identifier) == m_state.end())
	{
		return none;
	}
	auto& state = m_state.at(identifier);
	if (!state.isExist(current))
	{
		return none;
	}
	return Optional<AnimateState>(state.next(current));
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
		size_t pos = split[2].find_last_of('R');
		std::string name = split[2].substr(0, pos);
		bool isReversed = (pos != std::string::npos);

		m_state[split[0]].add(
			String::ToValue<int>(split[1]), String::ToValue<int>(name), isReversed);
	}
}
