# include "SingletonFinalizer.h"

SingletonFinalizer::Finalizers SingletonFinalizer::m_finalizers;

void SingletonFinalizer::AddFinalizer(const Finalizer& func)
{
	m_finalizers.push_back(func);
}

void SingletonFinalizer::Finalize()
{
	for (auto it = m_finalizers.rbegin(); it != m_finalizers.rend(); ++it)
	{
		(*it)();
	}
	m_finalizers.clear();
}
