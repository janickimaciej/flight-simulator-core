#include "app/exitSignal.hpp"

namespace App
{
	bool ExitSignal::shouldStop() const
	{
		return m_exiting;
	}

	void ExitSignal::exit(ExitCode exitCode)
	{
		std::scoped_lock lock{m_mutex};

		if (!m_exiting)
		{
			m_exiting = true;
			m_exitCode = exitCode;
			for (const std::function<void()>& callback : m_onExitCallbacks)
			{
				callback();
			}
		}
	}

	ExitCode ExitSignal::getExitCode() const
	{
		return m_exitCode;
	}

	void ExitSignal::registerOnExit(std::function<void()> callback)
	{
		std::scoped_lock lock{m_mutex};

		m_onExitCallbacks.push_back(callback);
	}
}
