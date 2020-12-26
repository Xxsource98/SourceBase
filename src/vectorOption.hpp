#pragma once
#include "option.hpp"

BEGIN_SOURCE_NS
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
END_SOURCE_NS