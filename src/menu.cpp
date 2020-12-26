#include "Menu.hpp"

BEGIN_SOURCE_NS
Menu::Menu(std::string menuName, MENU_STRUCT menuStruct)
{
	this->p_menuName = menuName;
	this->p_menuColors = menuStruct.menuColors;
	this->p_menuBinds = menuStruct.menuBinds;
	this->p_menuContrBinds = menuStruct.menuControllerBinds;
	this->p_delay = std::make_shared<Timer>(std::chrono::milliseconds(130));
	this->p_menuSize = Vec2(300.f, 90.f);
	this->p_menuPosition = Vec2(260.f, 100.f);
	this->p_currentSubmenu = "main";
	this->p_menuOpened = false;
	this->p_currentOption = 1;
	this->p_maxVisibleOptions = 9;
	this->p_submenuLevel = 0;
	this->p_controlsToDisable = {
		ControlPhone,
		ControlWeaponWheelUpDown,
		ControlWeaponWheelLeftRight,
		ControlWeaponWheelNext,
		ControlWeaponWheelPrev,
		ControlCharacterWheel,
		ControlMultiplayerInfo,
		ControlPhone,
		ControlMap,
		ControlPhoneUp,
		ControlPhoneDown,
		ControlPhoneLeft,
		ControlPhoneRight,
		ControlPhoneSelect,
		ControlPhoneCancel,
		ControlPhoneOption,
		ControlFrontendDown,
		ControlFrontendUp,
		ControlFrontendLeft,
		ControlFrontendRight,
		ControlFrontendRdown,
		ControlFrontendRup,
		ControlFrontendRleft,
		ControlFrontendRright,
		ControlFrontendAccept,
		ControlFrontendCancel,
		ControlSelectWeapon,
		ControlMeleeAttack1,
		ControlMeleeAttack2,
		ControlMeleeAttackAlternate,
		ControlMeleeAttackLight,
		ControlMeleeAttackHeavy,
		ControlReplayStartStopRecording,
		ControlReplayStartStopRecordingSecondary,
		ControlVehicleHorn,
		ControlNextCamera
	};
}

Menu::~Menu()
{
	for (auto option : this->p_menuOptions)
	{
		delete option;
	}
}

void Menu::draw(std::function<void(Menu* currentMenu)> menuOptions, std::function<void()> featuresLoop)
{
	this->listenKeyboard();

	if (this->p_menuOpened)
	{
		menuOptions(this);
		this->disableControls();
	}
	else this->enableControls();

	this->checkBinds();
	this->resetKeyboard();
	featuresLoop();
}

void Menu::addOption(Option* option) const
{
	this->p_menuOptions.push_back(option);
}

void Menu::registerSubmenu(std::string submenuName, std::string submenuID, std::function<void()> submenuElements) const
{
	if (!Utils::doesElementExistInVector<std::string>(this->p_menuSubmenus, submenuID))
		this->p_menuSubmenus.push_back(submenuID);

	if (this->p_menuOpened && (this->p_currentSubmenu == submenuID))
	{
		submenuElements();
		this->drawHeader();
		this->drawOptions();
		this->drawNavbar(submenuName);
		this->drawFooter();
	}
}

void Menu::setPosition(Vec2 newPosition) const
{
	this->p_menuPosition = newPosition;
}

void Menu::setColor(Enums::ColorType colorType, RGBA newColor) const
{
	switch (colorType)
	{
	case Enums::ColorType::MAIN_RECT:
		this->p_menuColors.mainRect = newColor;
		break;

	case Enums::ColorType::NAVBAR_RECT:
		this->p_menuColors.navbarRect = newColor;
		break;

	case Enums::ColorType::BACKGROUND:
		this->p_menuColors.background = newColor;
		break;

	case Enums::ColorType::FOOTER_RECT:
		this->p_menuColors.footerRect = newColor;
		break;

	case Enums::ColorType::DESCRIPTION_RECT:
		this->p_menuColors.descriptionRect = newColor;
		break;

	default:
		break;
	}
}

void Menu::setColor(Enums::ColorType colorType, RGBAF newColor) const
{
	switch (colorType)
	{
	case Enums::ColorType::RECT_TEXT:
		this->p_menuColors.mainText = newColor;
		break;

	case Enums::ColorType::NAVBAR_TEXT:
		this->p_menuColors.navbarText = newColor;
		break;

	case Enums::ColorType::OPTION_TEXT:
		this->p_menuColors.optionText = newColor;
		break;

	case Enums::ColorType::FOOTER_TEXT:
		this->p_menuColors.footerText = newColor;
		break;

	case Enums::ColorType::DESCRIPTION_TEXT:
		this->p_menuColors.descriptionText = newColor;
		break;

	default:
		break;
	}
}

void Menu::setName(std::string newName) const
{
	this->p_menuName = newName;
}

void Menu::setCurrentSubmenu(std::string newSubmenu) const
{
	if (!Utils::doesElementExistInVector(this->p_shownSubmenus, newSubmenu))
	{
		this->p_menuOptions.clear();
		this->p_showSubmenusLastOptions.push_back(this->p_currentOption);
		this->p_shownSubmenus.push_back(newSubmenu);
		this->p_currentSubmenu = newSubmenu;
		this->p_currentOption = 1;
		this->p_submenuLevel++;
	}
}

void Menu::setCurrentOption(std::uint32_t newValue) const
{
	this->p_currentOption = newValue;
}

void Menu::setMaxVisibleOptions(std::uint32_t newValue) const
{
	this->p_maxVisibleOptions = newValue;
}

void Menu::setPreviousSubmenu() const
{
	if (this->p_submenuLevel > 0)
	{
		std::string newSubmenu = this->p_shownSubmenus.at(static_cast<std::size_t>(this->p_submenuLevel - 1));
		std::uint32_t currentOption = this->p_showSubmenusLastOptions.at(static_cast<std::size_t>(this->p_submenuLevel - 1));

		if (Utils::doesElementExistInVector(this->p_menuSubmenus, newSubmenu))
		{
			this->p_currentSubmenu = newSubmenu;
			this->p_currentOption = currentOption;
			this->p_shownSubmenus.pop_back();
			this->p_showSubmenusLastOptions.pop_back();
			this->p_submenuLevel--;
		}
	}
	else
	{
		this->p_menuOpened = false;
		this->p_currentSubmenu = "null";
	}
}

const Vec2 Menu::getPosition() const
{
	return this->p_menuPosition;
}

const std::string Menu::getCurrentSubmenu() const
{
	return this->p_currentSubmenu;
}

const std::uint32_t Menu::getCurrentOption() const
{
	return this->p_currentOption;
}

const std::uint32_t Menu::getMaxVisibleOptions() const
{
	return this->p_maxVisibleOptions;
}

void Menu::playSound(const char* soundRef, const char* soundName) const
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, (char*)soundName, (char*)soundRef, FALSE);
}

void Menu::checkBinds() const
{
	if (this->p_pressedKeys.OPEN)
	{
		this->p_menuOpened = !this->p_menuOpened;
		if (this->p_currentSubmenu == "main" || this->p_currentSubmenu == "null")
		{
			this->p_shownSubmenus.clear();
			this->p_currentSubmenu = "main";
			this->p_shownSubmenus.push_back(this->p_currentSubmenu);
			this->p_submenuLevel = 0;
		}
		this->playSound("HUD_FRONTEND_DEFAULT_SOUNDSET", "CONTINUE");
	}

	if (this->p_menuOpened)
	{
		if (this->p_pressedKeys.UP)
		{
			if (this->p_currentOption == 1)
				this->p_currentOption = (std::uint32_t)this->p_menuOptions.size();
			else
				--this->p_currentOption;

			this->playSound("HUD_FRONTEND_DEFAULT_SOUNDSET", "NAV_UP_DOWN");
		}

		if (this->p_pressedKeys.DOWN)
		{
			if (this->p_currentOption > this->p_menuOptions.size() - 1)
				this->p_currentOption = 1;
			else
				++this->p_currentOption;

			this->playSound("HUD_FRONTEND_DEFAULT_SOUNDSET", "NAV_UP_DOWN");
		}

		if (this->p_pressedKeys.LEFT || this->p_pressedKeys.RIGHT)
		{
			this->playSound("HUD_FRONTEND_DEFAULT_SOUNDSET", "NAV_UP_DOWN");
		}

		if (this->p_pressedKeys.BACK)
		{
			this->setPreviousSubmenu();
			this->playSound("HUD_FRONTEND_DEFAULT_SOUNDSET", "BACK");
		}
	}
}

void Menu::listenKeyboard() const
{
	if (IsKeyJustUp(this->p_menuBinds.OPEN) || isControllerJustDown(this->p_menuContrBinds.OPEN))
	{
		this->p_pressedKeys.OPEN = true;
	}
	if (IsKeyJustUp(this->p_menuBinds.UP) || isControllerJustDown(this->p_menuContrBinds.UP))
	{
		this->p_pressedKeys.UP = true;
	}
	if (IsKeyJustUp(this->p_menuBinds.DOWN) || isControllerJustDown(this->p_menuContrBinds.DOWN))
	{
		this->p_pressedKeys.DOWN = true;
	}
	if (IsKeyJustUp(this->p_menuBinds.LEFT) || isControllerJustDown(this->p_menuContrBinds.LEFT))
	{
		this->p_pressedKeys.LEFT = true;
	}
	if (IsKeyJustUp(this->p_menuBinds.RIGHT) || isControllerJustDown(this->p_menuContrBinds.RIGHT))
	{
		this->p_pressedKeys.RIGHT = true;
	}
	if (IsKeyJustUp(this->p_menuBinds.ACCEPT) || isControllerJustDown(this->p_menuContrBinds.ACCEPT))
	{
		this->p_pressedKeys.ACCEPT = true;
	}
	if (IsKeyJustUp(this->p_menuBinds.BACK) || isControllerJustDown(this->p_menuContrBinds.BACK))
	{
		this->p_pressedKeys.BACK = true;
	}
}

void Menu::resetKeyboard() const
{
	this->p_menuOptions.clear();
	this->p_pressedKeys.ACCEPT = false;
	this->p_pressedKeys.BACK = false;
	this->p_pressedKeys.OPEN = false;
	this->p_pressedKeys.UP = false;
	this->p_pressedKeys.DOWN = false;
	this->p_pressedKeys.LEFT = false;
	this->p_pressedKeys.RIGHT = false;
}

void Menu::enableControls() const
{
	if (!this->p_menuOpened)
	{
		for (auto e : this->p_controlsToDisable)
		{
			CONTROLS::ENABLE_CONTROL_ACTION(0, e, TRUE);
		}
	}
}

void Menu::disableControls() const
{
	for (auto e : this->p_controlsToDisable)
	{
		CONTROLS::DISABLE_CONTROL_ACTION(0, e, TRUE);
	}
}

void Menu::drawHeader() const
{
	Utils::drawRect(this->p_menuPosition, this->p_menuSize, this->p_menuColors.mainRect);

	Utils::drawText(this->p_menuName,
		Vec2(this->p_menuPosition.Get().x, this->p_menuPosition.Get().y - 15.f),
		90.f, this->p_menuColors.mainText, true);
}

void Menu::drawNavbar(std::string submenuName) const
{
	Utils::drawRect(this->p_menuPosition + Vec2(0.f, this->p_menuSize.Get().y / 1.5f),
		Vec2(this->p_menuSize.Get().x, 30.f),
		this->p_menuColors.navbarRect);

	Utils::drawText(submenuName,
		this->p_menuPosition + Vec2(-(this->p_menuSize.Get().x / 2.0689f), this->p_menuSize.Get().y / 1.8947f),
		50.f, this->p_menuColors.navbarText);

	Utils::drawText(std::string(std::to_string(this->p_currentOption) + " / " + std::to_string(this->p_menuOptions.size())),
		this->p_menuPosition + Vec2(this->p_menuSize.Get().x / 2.0689f, this->p_menuSize.Get().y / 1.8947f),
		50.f, this->p_menuColors.navbarText, false, true);
}

void Menu::drawOptionValues(Option* option, int currentOption, bool isSelected) const
{
	if (option->getOptionType() == "Submenu")
	{
		Utils::drawSprite("commonmenu", "arrowright",
			this->p_menuPosition + Vec2((this->p_menuSize.Get().x / 2.21f), currentOption * 30.f + (this->p_menuSize.Get().y / 1.5f)),
			Vec2(27.f, 27.f), isSelected ? RGBA(this->p_menuColors.selectedOptionText) : RGBA(this->p_menuColors.optionText));
	}

	if (option->getOptionType() == "Toggle")
	{
		const bool boolState = option->getBooleanValue();
		const char* currentSprite = isSelected ? (boolState ? "shop_box_tickb" : "shop_box_blankb") : (boolState ? "shop_box_tick" : "shop_box_blank");

		Utils::drawSprite("commonmenu", currentSprite,
			this->p_menuPosition + Vec2((this->p_menuSize.Get().x / 2.21f), currentOption * 30.f + (this->p_menuSize.Get().y / 1.5f)),
			Vec2(38.5f, 38.5f), RGBA(255, 255, 255));
	}

	if (option->getOptionType() == "Slider")
	{
		if (option->getSliderType() != Enums::SLIDER_TYPE::NONE)
		{
			bool isInteger = option->getSliderType() == Enums::SLIDER_TYPE::INT;
			float value = isInteger ? *option->getIntegerAddress() : *option->getFloatAddress();
			float max = isInteger ? option->getIntegerMax() : option->getFloatMax();
			std::string optionText = "";

			if (!isInteger)
			{
				int secondNumber = static_cast<int>((fmod(value, 1) * 10.0) * 10);
				int maxSecondNumber = static_cast<int>((fmod(max, 1) * 10.0) * 10);

				optionText = std::string(std::to_string((int)value) + "." + std::to_string(secondNumber).substr(0, 2))
					+ " / " +
					std::string(std::to_string((int)max) + "." + std::to_string(maxSecondNumber).substr(0, 2));
			}
			else
				optionText = std::to_string((int)value) + " / " + std::to_string((int)max);


			Utils::drawText(optionText,
				this->p_menuPosition + Vec2((this->p_menuSize.Get().x / 2.0689f) - (isSelected ? 20.f : 0.f), currentOption * 30.f + (this->p_menuSize.Get().y / 1.8947f)),
				50.f,
				isSelected ? this->p_menuColors.selectedOptionText : this->p_menuColors.optionText, false, true);

			if (isSelected)
			{
				Utils::drawSprite("commonmenu", "shop_arrows_upanddown",
					this->p_menuPosition + Vec2((this->p_menuSize.Get().x / 2.21f), currentOption * 30.f + (this->p_menuSize.Get().y / 1.5f)),
					Vec2(25.f, 25.f), isSelected ? RGBA(this->p_menuColors.selectedOptionText) : RGBA(this->p_menuColors.optionText), 90);
			}
		}
	}

	if (option->getOptionType() == "Vector")
	{
		Utils::drawText(option->getVectorValue(*option->getIntegerAddress()),
			this->p_menuPosition + Vec2((this->p_menuSize.Get().x / 2.0689f) - (isSelected ? 20.f : 0.f), currentOption * 30.f + (this->p_menuSize.Get().y / 1.8947f)),
			50.f,
			isSelected ? this->p_menuColors.selectedOptionText : this->p_menuColors.optionText, false, true);

		if (isSelected)
		{
			Utils::drawSprite("commonmenu", "shop_arrows_upanddown",
				this->p_menuPosition + Vec2((this->p_menuSize.Get().x / 2.21f), currentOption * 30.f + (this->p_menuSize.Get().y / 1.5f)),
				Vec2(25.f, 25.f), isSelected ? RGBA(this->p_menuColors.selectedOptionText) : RGBA(this->p_menuColors.optionText), 90);
		}
	}
}

void Menu::initOptionActions(Option* option, bool isSelected) const
{
	if (isSelected)
	{
		if (this->p_pressedKeys.ACCEPT)
		{
			if (option->getOptionType() == "Toggle")
			{
				option->setBooleanValue(!option->getBooleanValue());
			}

			if (option->getOptionType() == "Submenu")
			{
				this->setCurrentSubmenu(option->getSubmenu());
			}

			option->useFunction();
		}

		if (this->p_pressedKeys.LEFT)
		{
			if (option->getSliderType() != Enums::SLIDER_TYPE::NONE)
			{
				bool isInteger = option->getSliderType() == Enums::SLIDER_TYPE::INT;
				float value = isInteger ? *option->getIntegerAddress() : *option->getFloatAddress();
				float min = isInteger ? option->getIntegerMin() : option->getFloatMin();
				float max = isInteger ? option->getIntegerMax() : option->getFloatMax();
				float step = isInteger ? option->getIntegerStep() : option->getFloatStep();
				const float newValue = value -= step;

				isInteger ?
					option->setIntegerValue(static_cast<int>(value < min ? max : newValue)) :
					option->setFloatValue(value < min ? max : newValue);
			}

			option->useFunction();
		}

		if (this->p_pressedKeys.RIGHT)
		{
			if (option->getSliderType() != Enums::SLIDER_TYPE::NONE)
			{
				bool isInteger = option->getSliderType() == Enums::SLIDER_TYPE::INT;
				float value = isInteger ? *option->getIntegerAddress() : *option->getFloatAddress();
				float min = isInteger ? option->getIntegerMin() : option->getFloatMin();
				float max = isInteger ? option->getIntegerMax() : option->getFloatMax();
				float step = isInteger ? option->getIntegerStep() : option->getFloatStep();
				const float newValue = value += step;

				isInteger ?
					option->setIntegerValue(static_cast<int>(value > max ? min : newValue)) :
					option->setFloatValue(value > max ? min : newValue);
			}

			option->useFunction();
		}
	}

}

void Menu::drawOption(Option* option, std::uint32_t ID) const
{
	bool isSelected = (this->p_currentOption >= this->p_maxVisibleOptions ? this->p_maxVisibleOptions : this->p_currentOption) == ID;

	this->initOptionActions(option, isSelected);

	Utils::drawRect(this->p_menuPosition + Vec2(0.f, ID * 30.f + (this->p_menuSize.Get().y / 1.5f)),
		Vec2(this->p_menuSize.Get().x, 30.f),
		isSelected ? this->p_menuColors.scroller : this->p_menuColors.background);

	Utils::drawText(option->getLeftText(),
		this->p_menuPosition + Vec2(-(this->p_menuSize.Get().x / 2.0689f), ID * 30.f + (this->p_menuSize.Get().y / 1.8947f)),
		50.f,
		isSelected ? this->p_menuColors.selectedOptionText : this->p_menuColors.optionText);

	Utils::drawText(option->getRightText(),
		this->p_menuPosition + Vec2((this->p_menuSize.Get().x / 2.0689f), ID * 30.f + (this->p_menuSize.Get().y / 1.8947f)),
		50.f,
		isSelected ? this->p_menuColors.selectedOptionText : this->p_menuColors.optionText, false, true);

	this->drawOptionValues(option, ID, isSelected);

	isSelected ? this->drawInfo(option) : void();
}

void Menu::drawOptions() const
{
	static int curOption = 0;

	std::vector<Option*> options = this->p_menuOptions;
	std::uint32_t totalSize = (std::uint32_t)options.size();
	std::uint32_t currentOption = this->p_currentOption;
	std::uint32_t maxVisOptions = this->p_maxVisibleOptions;
	std::uint32_t start = 0;
	std::uint32_t end = totalSize > maxVisOptions ? maxVisOptions : totalSize;

	if ((totalSize > maxVisOptions) && (currentOption > maxVisOptions))
	{
		start = currentOption - maxVisOptions;
		end = currentOption;
	}

	for (std::uint32_t i = start; i < end; i++)
	{
		drawOption(options.at(i), curOption);
		curOption++;
	}

	curOption = 1;
}

void Menu::drawFooter() const
{
	std::uint32_t size = (int)this->p_menuOptions.size();
	std::uint32_t maxVis = this->p_maxVisibleOptions;
	int optionID = size > maxVis ? maxVis + 1 : size + 1;

	Utils::drawRect(this->p_menuPosition + Vec2(0.f, optionID * 30.f + (this->p_menuSize.Get().y / 1.5f)),
		Vec2(this->p_menuSize.Get().x, 30.f),
		this->p_menuColors.footerRect);

	Utils::drawText(MENU_VERSION,
		this->p_menuPosition + Vec2(-(this->p_menuSize.Get().x / 2.0689f), optionID * 30.f + (this->p_menuSize.Get().y / 1.8947f)),
		50.f,
		this->p_menuColors.footerText);

	Utils::drawSprite("commonmenu", "shop_arrows_upanddown",
		this->p_menuPosition + Vec2(0.f, optionID * 30.f + (this->p_menuSize.Get().y / 1.5f)),
		Vec2(30.f, 30.f), RGBA(this->p_menuColors.optionText));
}

void Menu::drawInfo(Option* option) const
{
	if (!option->getDescription().empty())
	{
		std::uint32_t size = (std::uint32_t)this->p_menuOptions.size();
		std::uint32_t maxVis = this->p_maxVisibleOptions;
		std::uint32_t descriptionSize = (std::uint32_t)option->getDescription().size();
		int optionID = size > maxVis ? maxVis + 2 : size + 2;
		constexpr std::uint32_t maxChars = 46; // 42
		std::uint32_t descriptionLines = static_cast<int>(descriptionSize / maxChars);
		float descriptionMath = descriptionLines == 0 ? descriptionLines + 1 : (descriptionLines + 1) * (6.f + (descriptionLines * 2)); 

		Utils::drawRect(this->p_menuPosition + Vec2(0.f, optionID * 30.f + (this->p_menuSize.Get().y / 1.5f) - 8.f),
			Vec2(this->p_menuSize.Get().x, 2.5f),
			this->p_menuColors.descriptionLine);

		Utils::drawRect(this->p_menuPosition + Vec2(0.f, optionID * 30.f + (this->p_menuSize.Get().y / 1.5f) + 8.f + descriptionMath),
			Vec2(this->p_menuSize.Get().x, (descriptionLines + 1) * 30.f),
			this->p_menuColors.descriptionRect);

		Utils::drawText(std::string(option->getDescription()),
			this->p_menuPosition + Vec2(-(this->p_menuSize.Get().x / 2.0689f), optionID * 30.f + (this->p_menuSize.Get().y / 1.8947f) + 8.f),
			50.f,
			this->p_menuColors.descriptionText, false, false, false, 0.2642f);
	}
}
END_SOURCE_NS