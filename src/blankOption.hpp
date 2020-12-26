#pragma once
#include "option.hpp"

BEGIN_SOURCE_NS
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
END_SOURCE_NS