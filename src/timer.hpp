#pragma once
#include <chrono>
#include <functional>
#include <thread>
#include "constVariables.hpp"

namespace Source {
	class Timer
	{
	public:
		/* Do the reset after every use */
		explicit Timer(std::chrono::milliseconds delay)
		{
			this->p_now = std::chrono::high_resolution_clock::now();
			this->p_delay = delay;
		}

		void WaitThen(std::function<void()> callback)
		{
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();
			if ((now.time_since_epoch().count() - this->p_now.time_since_epoch().count()) >= this->p_delay.count())
			{
				callback();
			}
		}

		void Reset()
		{
			this->p_now = std::chrono::high_resolution_clock::now();
		}
	private:
		std::chrono::steady_clock::time_point p_now;
		std::chrono::steady_clock::duration p_delay;
	};
}