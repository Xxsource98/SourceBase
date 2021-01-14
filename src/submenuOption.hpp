#pragma once
#include "option.hpp"

namespace Source {
	namespace Options
	{
		class SubmenuOption : public Option
		{
		public:
			/*I don't know if texts in game has any limitations, but description won't display big strings (I don't really know why)*/
			SubmenuOption(std::string optionText, std::string newSubmenu, std::string optionDescription = "", std::function<void()> optionCallback = [] {})
				: Option(std::move(optionText), "", std::move(optionDescription), std::move(optionCallback), 0, 0, 0, 0, 0, 0, 0, 0, nullptr, 0, std::move(newSubmenu))
			{
				this->setOptionType("Submenu");
			}
		};
	}
}