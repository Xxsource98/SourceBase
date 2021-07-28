/*
	Last Update Date: 2021-07-28
	Trainer Base Created by: Xxsource98
	Github Link: https://github.com/Xxsource98/SourceBase
	Project License: GNU General Public License v3.0
	Base Version: 1.1
*/

#pragma once
#include "option.hpp"

namespace Source 
{
	namespace Options
	{
		class BlankOption : public Option
		{
		public:
			/*I don't know if texts in game has any limitations, but description won't display big strings (I don't really know why)*/
			BlankOption(std::string optionText, std::string optionDescription = "", std::function<void()> optionCallback = [] {})
				: Option(std::move(optionText), "", std::move(optionDescription), std::move(optionCallback))
			{
				this->setOptionType("Blank");
			}
		};
	}
}