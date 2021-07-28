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
		class SliderOption : public Option
		{
		public:
			/* Supporting: int, float */
			/*I don't know if texts in game has any limitations, but description won't display big strings (I don't really know why)*/
			SliderOption(std::string optionText, int* sliderSource, int min, int max, int step = 1, std::string optionDescription = "", std::function<void()> optionCallback = [] {})
				: Option(std::move(optionText), "", std::move(optionDescription), std::move(optionCallback), std::move(sliderSource), std::move(min), std::move(max), std::move(step))
			{
				this->setOptionType("Slider");
				this->setSliderType(Enums::SLIDER_TYPE::INT);
			}

			SliderOption(std::string optionText, float* sliderSource, float min, float max, float step = 1, std::string optionDescription = "", std::function<void()> optionCallback = [] {})
				: Option(std::move(optionText), "", std::move(optionDescription), std::move(optionCallback), nullptr, 0, 0, 0, std::move(sliderSource), std::move(min), std::move(max), std::move(step))
			{
				this->setOptionType("Slider");
				this->setSliderType(Enums::SLIDER_TYPE::FLOAT);
			}
		};
	}
}