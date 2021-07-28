/*
	Last Update Date: 2021-07-28
	Trainer Base Created by: Xxsource98
	Github Link: https://github.com/Xxsource98/SourceBase
	Project License: GNU General Public License v3.0
	Base Version: 1.1
*/

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