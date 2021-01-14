/*
	Last Update Date: 2020-12-25
	Trainer Base Created by: Xxsource98
	Github Link:
	Project License: GNU General Public License v3.0
	Base Version: 1.0
*/

#pragma once
#include <Windows.h>
#include <string>
#include <natives.h>
#include <enums.h>
#include "structs.hpp"
#include "timer.hpp"
#include "option.hpp"
#include "constVariables.hpp"
#include "utils.hpp"
#include "keyboard.hpp"

namespace Source {
	using namespace Structs;

	class Menu
	{
	public:
		explicit Menu(std::string menuName, MENU_STRUCT menuStruct);
		~Menu();

		/*
		-> menuOptions function is the main loop of menu. You can create that with creating another void with parameter: Menu* currentMenu, and create options reffering to first parameter.
		-> featuresLoop function is the your void with all features loop. */
		void draw(std::function<void(Menu* currentMenu)> menuOptions, std::function<void()> featuresLoop);
		/* You can see the all options on Source::Options namespace */
		void addOption(Option* option) const;
		/* Every submenu you have to register and put necessary options in it */
		void registerSubmenu(std::string submenuName, std::string submenuID, std::function<void()> submenuElements) const;

		void setPosition(Vec2 newPosition) const;
		void setColor(Enums::ColorType colorType, RGBA newColor) const;
		void setColor(Enums::ColorType colorType, RGBAF newColor) const;
		void setName(std::string newName) const;
		void setCurrentSubmenu(std::string newSubmenu) const;
		void setCurrentOption(std::uint32_t newValue) const;
		void setMaxVisibleOptions(std::uint32_t newValue) const;
		void setPreviousSubmenu() const;

		const Vec2 getPosition() const;
		const std::string getCurrentSubmenu() const;
		const std::uint32_t getCurrentOption() const;
		const std::uint32_t getMaxVisibleOptions() const;

	private:
		void playSound(const char* soundRef, const char* soundName) const;

		void checkBinds() const;
		void listenKeyboard() const;
		void resetKeyboard() const;

		void enableControls() const;
		void disableControls() const;

		void drawHeader() const;
		void drawNavbar(std::string submenuName) const;
		void drawOptionValues(Option* option, int currentOption, bool isSelected) const;
		void initOptionActions(Option* option, bool isSelected) const;
		void drawOption(Option* option, std::uint32_t ID) const;
		void drawOptions() const;
		void drawFooter() const;
		void drawInfo(Option* option) const;

	private:
		std::shared_ptr<Timer> p_delay;
		mutable std::vector<Option*> p_menuOptions;
		mutable std::vector<std::string> p_menuSubmenus;
		mutable std::vector<std::string> p_shownSubmenus;
		mutable std::vector<std::uint32_t> p_showSubmenusLastOptions;
		mutable std::vector<eControl> p_controlsToDisable;
		mutable std::string p_menuName;
		mutable MENU_COLORS p_menuColors;
		mutable MENU_BINDS p_menuBinds;
		mutable MENU_CONTROLLER_BINDS p_menuContrBinds;
		mutable Vec2 p_menuSize;
		mutable Vec2 p_menuPosition;
		mutable PRESSED_KEYS p_pressedKeys;
		mutable std::string p_currentSubmenu;
		mutable std::string p_lastSubmenu;
		mutable std::uint32_t p_submenuLevel;
		mutable std::uint32_t p_lastOption;
		mutable std::uint32_t p_currentOption;
		mutable std::uint32_t p_maxVisibleOptions;
		mutable bool p_menuOpened;
	};
}