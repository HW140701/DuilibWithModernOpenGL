#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <mutex>

template<typename T>
class Singleton
{
public:
	//获取全局单例对象
	template<typename ...Args>
	static std::shared_ptr<T> GetInstance(Args&&... args)
	{
		if (!m_pSingleton)
		{
			std::lock_guard<std::mutex> gLock(m_Mutex);

			if (nullptr == m_pSingleton)
			{
				m_pSingleton = std::make_shared<T>(std::forward<Args>(args)...);
			}
		}
		return m_pSingleton;
	}

private:
	explicit Singleton();
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	~Singleton() = default;

private:
	static std::shared_ptr<T> m_pSingleton;
	static std::mutex m_Mutex;
};

template<typename T>
std::shared_ptr<T> Singleton<T>::m_pSingleton = nullptr;

template<typename T>
std::mutex Singleton<T>::m_Mutex;

#endif
