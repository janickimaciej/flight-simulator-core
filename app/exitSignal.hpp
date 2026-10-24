#pragma once

#include "app/exitCode.hpp"

#include <atomic>
#include <functional>
#include <mutex>
#include <vector>

namespace App
{
	class ExitSignal
	{
	public:
		bool exiting() const;
		void exit(ExitCode exitCode);
		ExitCode getExitCode() const;
		void registerOnExit(const std::function<void()>& callback);

	private:
		std::atomic<bool> m_exiting = false;
		std::atomic<ExitCode> m_exitCode{};
		std::vector<std::function<void()>> m_onExitCallbacks{};
		std::mutex m_mutex{};
	};
}
