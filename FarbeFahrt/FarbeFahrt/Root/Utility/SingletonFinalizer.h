# pragma once

# include <functional>
# include <vector>
# include <mutex>
# include <cassert>

class SingletonFinalizer
{
public:

	using Finalizer = std::function<void()>;

	using Finalizers = std::vector<Finalizer>;

public:

	static void AddFinalizer(const Finalizer& func);

	static void Finalize();

private:

	static Finalizers m_finalizers;
};

template <typename Type>
class Singleton final
{
public:

	static Type& Instance()
	{
		std::call_once(m_isInit, Create);
		if (!m_instance)
		{
			throw std::exception("シングルトンなインスタンスが生成できませんでした");
		}
		return *m_instance;
	}

private:

	static void Create()
	{
		m_instance = new Type;
		SingletonFinalizer::AddFinalizer(&Singleton<Type>::Destroy);
	}

	static void Destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}

	static std::once_flag m_isInit;

	static Type* m_instance;
};

template <typename Type>
std::once_flag Singleton<Type>::m_isInit;

template <typename Type>
Type* Singleton<Type>::m_instance = nullptr;
