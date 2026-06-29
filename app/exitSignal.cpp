#include "app/exitSignal.hpp"

#include "app/exitCode.hpp"

#include <atomic>
#include <mutex>
#include <semaphore>

namespace App
{
	bool ExitSignal::shouldStop() const
	{
		return m_exiting;
	}

	void ExitSignal::exit(ExitCode exitCode)
	{
		m_mutex.lock();

		if (!m_exiting)
		{
			m_exiting = true;
			m_exitCode = exitCode;
			for (const std::function<void()>& callback : m_onExitCallbacks)
			{
				callback();
			}
		}

		m_mutex.unlock();
	}

	ExitCode ExitSignal::getExitCode() const
	{
		return m_exitCode;
	}

	void ExitSignal::registerOnExit(std::function<void()> callback)
	{
		m_mutex.lock();

		m_onExitCallbacks.push_back(callback);

		m_mutex.unlock();
	}
}
