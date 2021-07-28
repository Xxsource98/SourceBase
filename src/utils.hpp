/*
	Last Update Date: 2021-07-28
	Trainer Base Created by: Xxsource98
	Github Link: https://github.com/Xxsource98/SourceBase
	Project License: GNU General Public License v3.0
	Base Version: 1.1
*/

#pragma once
#include <natives.h>
#include <enums.h>
#include "structs.hpp"

static void EnableDebugConsole()
{
	AllocConsole();
	auto fp = freopen("CONOUT$", "w", stdout);
}

#ifndef NDEBUG
	#define DO_DEBUG(func) func()
	#define ENABLE_CONSOLE EnableDebugConsole()
	#define FREE_CONSOLE FreeConsole()
#else 
	#define DO_DEBUG(func) void()
	#define ENABLE_CONSOLE void()
	#define FREE_CONSOLE void()
#endif

namespace Utils
{
	/* delayTime in miliseconds, default is 5000 (5s) */
	inline void messageBottom(std::string message, std::uint32_t delayTime = 5000)
	{
		UI::BEGIN_TEXT_COMMAND_PRINT((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)message.c_str());
		UI::END_TEXT_COMMAND_PRINT(delayTime, TRUE);
	}

	inline void messageMap(std::string message)
	{
		UI::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)message.c_str());
		UI::_DRAW_NOTIFICATION_3(FALSE, FALSE);
	}

	template <typename Type>
	inline bool doesElementExistInVector(std::vector<Type> vector, Type valueToFind)
	{
		for (auto element : vector)
		{
			if (element == valueToFind)
				return true;
			else continue;
		}

		return false;
	}

	inline const Structs::Vec2 screenResolution()
	{
		int screenWidth, screenHeight;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screenWidth, &screenHeight);

		return Structs::Vec2((float)screenWidth, (float)screenHeight);
	}

	inline const void drawRect(Structs::Vec2 rectCoords, Structs::Vec2 rectSize, Structs::RGBA rectColor)
	{
		const auto resolution = screenResolution();

		GRAPHICS::DRAW_RECT(
			rectCoords.Get().x / resolution.Get().x,
			rectCoords.Get().y / resolution.Get().y,
			rectSize.Get().x / resolution.Get().x, 
			rectSize.Get().y / resolution.Get().y,
			rectColor.r, rectColor.g, rectColor.b, rectColor.a
		);
	}

	inline const void drawText(std::string text, Structs::Vec2 textPosition, float fontSize, Structs::RGBAF textFontColor, bool centre = false, bool rightAlign = false, bool outline = false, float textWrap = 1.5f)
	{
		const auto resolution = screenResolution();

		const Structs::Vec2 newPosition(
			textPosition.Get().x / resolution.Get().x,
			textPosition.Get().y / resolution.Get().y
		);

		UI::SET_TEXT_FONT(textFontColor.f);
		UI::SET_TEXT_SCALE(0.f, fontSize / 100);
		UI::SET_TEXT_COLOUR(textFontColor.r, textFontColor.g, textFontColor.b, textFontColor.a);
		outline ? UI::SET_TEXT_OUTLINE() : void();
		UI::SET_TEXT_CENTRE(centre);
		UI::SET_TEXT_WRAP(0.f, newPosition.Get().x + textWrap);
		if (rightAlign)
		{
			UI::SET_TEXT_WRAP(0.f, newPosition.Get().x);
			UI::SET_TEXT_RIGHT_JUSTIFY(true);
		}
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)std::string(text).c_str());
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(newPosition.Get().x, newPosition.Get().y);
	}

	inline const void drawSprite(const char* textureDict, const char* textureName, Structs::Vec2 spritePosition, Structs::Vec2 spriteSize, Structs::RGBA spriteColor, int rotation = 0)
	{
		const auto resolution = screenResolution();

		const Structs::Vec2 newPosition(
			spritePosition.Get().x / resolution.Get().x,
			spritePosition.Get().y / resolution.Get().y
		);

		const Structs::Vec2 newSize(
			spriteSize.Get().x / resolution.Get().x,
			spriteSize.Get().y / resolution.Get().y
		);
		
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)textureDict))
		{
			GRAPHICS::DRAW_SPRITE((char*)textureDict, (char*)textureName,
				newPosition.Get().x, newPosition.Get().y,
				newSize.Get().x, newSize.Get().y,
				(float)rotation,
				spriteColor.r, spriteColor.g, spriteColor.b, spriteColor.a);
		}
		else GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)textureDict, FALSE);
	}
}