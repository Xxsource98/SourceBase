/*
	Last Update Date: 2020-12-25
	Trainer Base Created by: Xxsource98
	Github Link:
	Project License: GNU General Public License v3.0
	Base Version: 1.0
*/

#include <main.h>
#include "script.hpp"
#include "menu.hpp"
#include "structs.hpp"
#include <natives.h>
#include "blankOption.hpp"
#include "toggleOption.hpp"
#include "sliderOption.hpp"
#include "vectorOption.hpp"
#include "utils.hpp"
#include "submenuOption.hpp"

bool m_Godmode = false;
bool m_SuperJump = false;
int m_WantedLevel = 0;
int m_VectorInteger = 0;
std::vector<std::string> m_Vector = { "Red", "Green", "Blue" };

void MenuOptions(Source::Menu* curMenu)
{
	using namespace Source;

	static auto position = curMenu->getPosition().Get();

	curMenu->registerSubmenu("Main Menu", "main", [curMenu] {
		curMenu->addOption(new Options::SliderOption("Position X", &position.x, 0.f, 1100.f, 10.f, "", [curMenu] {
			curMenu->setPosition(Vec2(position.x, position.y));
			}));

		curMenu->addOption(new Options::SliderOption("Position Y", &position.y, 0.f, 1200.f, 10.f, "Example Float Slider Option", [curMenu] {
			curMenu->setPosition(Vec2(position.x, position.y));
			}));

		curMenu->addOption(new Options::ToggleOption("Godmode", &m_Godmode, "Example Bool Option"));
		curMenu->addOption(new Options::ToggleOption("Super Jump", &m_SuperJump, "Example Bool Option"));

		curMenu->addOption(new Options::SliderOption("Wanted Level", &m_WantedLevel, 0, 5, 1, "Example Int Slider Option", [] {
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), m_WantedLevel, FALSE);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), TRUE);
			}));

		curMenu->addOption(new Options::BlankOption("Show Zone", "Notify Player's Current Zone", [] {
			Vec3 playerPos(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE));

			Utils::messageMap(UI::_GET_LABEL_TEXT((char*)playerPos.getGamezone()));
			}));

		curMenu->addOption(new Options::VectorOption("Header Color", &m_Vector, &m_VectorInteger, "Example Vector Slider Option", [curMenu] {
			switch (m_VectorInteger)
			{
			case 0:
				curMenu->setColor(Enums::ColorType::MAIN_RECT, RGBA(245, 59, 87, 245));
				break;
			case 1:
				curMenu->setColor(Enums::ColorType::MAIN_RECT, RGBA(76, 209, 55, 245));
				break;
			case 2:
				curMenu->setColor(Enums::ColorType::MAIN_RECT, RGBA(0, 168, 255, 245));
				break;

			default: break;
			}
			}));

		curMenu->addOption(new Options::SubmenuOption("Example Sub", "test1", "Jump to another sub!"));
	});

	curMenu->registerSubmenu("Example Test", "test1", [curMenu] {
		for (int i = 0; i < 30; i++)
		{
			if (i == 5)
				curMenu->addOption(new Options::BlankOption("Blank 5", "Simple Blank Option 1"));
			else if (i == 15)
				curMenu->addOption(new Options::BlankOption("Half", "Simple Blank Option 2"));
			else
				curMenu->addOption(new Options::BlankOption("Blank", "Simple Blank Option"));
		}
		});
}

void FeaturesLoop()
{
	PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), m_Godmode);

	if (m_SuperJump)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	}
}

void Source::MainLoop()
{
	MENU_STRUCT menuStruct;
	menuStruct.menuColors.mainRect = RGBA(108, 92, 231, 245); // Example overwrite on the main menu struct

	const std::shared_ptr<Menu> menu = std::make_shared<Menu>("Source Base", menuStruct);

	while (true)
	{
		menu->draw(MenuOptions, FeaturesLoop);
		WAIT(0);
	}
}
