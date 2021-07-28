/*
	Last Update Date: 2021-07-28
	Trainer Base Created by: Xxsource98
	Github Link: https://github.com/Xxsource98/SourceBase
	Project License: GNU General Public License v3.0
	Base Version: 1.1
*/

#pragma once
#include "option.hpp"

namespace Source {
	namespace Options
	{
		class VectorOption : public Option
		{
		public:
			/* Supporting: std::vector<std::string> */
			/*I don't know if texts in game has any limitations, but description won't display big strings (I don't really know why)*/
			VectorOption(std::string optionText, std::vector<std::string>* optionVector, int* optionInteger, std::string optionDescription = "", std::function<void()> optionCallback = [] {})
				: Option(std::move(optionText), "", std::move(optionDescription), std::move(optionCallback), std::move(optionInteger), 0, std::move((int)optionVector->size() - 1), 1, nullptr, 0.f, 0.f, 0.f, nullptr, std::move(optionVector))
			{
				this->setOptionType("Vector");
				this->setSliderType(Enums::SLIDER_TYPE::INT);
			}
		};
	}
}