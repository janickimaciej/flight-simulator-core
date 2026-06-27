#pragma once

#include "app/exitCode.hpp"

#include <atomic>
#include <functional>
#include <mutex>
#include <semaphore>

namespace App
{
	class ExitSignal
	{
	public:
		bool shouldStop() const;
		void exit(ExitCode exitCode);
		ExitCode getExitCode() const;
		void registerOnExit(std::function<void()> callback);

	private:
		std::atomic<bool> m_exiting = false;
		ExitCode m_exitCode{};
		std::vector<std::function<void()>> m_onExitCallbacks{};
		std::mutex m_mutex{};
	};
}
