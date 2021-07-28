/*
	Last Update Date: 2021-07-28
	Trainer Base Created by: Xxsource98
	Github Link: https://github.com/Xxsource98/SourceBase
	Project License: GNU General Public License v3.0
	Base Version: 1.1
*/

#pragma once
#include <Windows.h>
#include <iostream>
#include <types.h>
#include <enums.h>
#include <functional>
#include <natives.h>

namespace Enums
{
	enum class ColorType : int
	{
		MAIN_RECT = -1,
		RECT_TEXT,
		NAVBAR_RECT,
		NAVBAR_TEXT,
		BACKGROUND,
		OPTION_TEXT,
		FOOTER_RECT,
		FOOTER_TEXT,
		DESCRIPTION_RECT,
		DESCRIPTION_TEXT
	};

	enum class SLIDER_TYPE : int
	{
		NONE = -5,
		INT = 0,
		FLOAT
	};
};

namespace Structs
{
	class RGBAF
	{
	public:
		RGBAF(std::uint32_t Red = 0U, std::uint32_t Green = 0U, std::uint32_t Blue = 0U, std::uint32_t Alpha = 255U, std::uint32_t Font = eFont::FontHouseScript)
			: r(Red), g(Green), b(Blue), a(Alpha), f(Font) {}

		std::uint32_t r = 0U;
		std::uint32_t g = 0U;
		std::uint32_t b = 0U;
		std::uint32_t a = 255U;
		std::uint32_t f = eFont::FontHouseScript;
	};

	class RGBA
	{
	public:
		RGBA(std::uint32_t Red = 0U, std::uint32_t Green = 0U, std::uint32_t Blue = 0U, std::uint32_t Alpha = 255U)
			: r(Red), g(Green), b(Blue), a(Alpha) {}

		RGBA(RGBAF rgba)
			: r(rgba.r), g(rgba.g), b(rgba.b), a(rgba.a) {}

		std::uint32_t r = 0U;
		std::uint32_t g = 0U;
		std::uint32_t b = 0U;
		std::uint32_t a = 255U;
	};

	struct MENU_BINDS
	{
		std::uint32_t OPEN = VK_INSERT;
		std::uint32_t UP = VK_UP;
		std::uint32_t DOWN = VK_DOWN;
		std::uint32_t LEFT = VK_LEFT;
		std::uint32_t RIGHT = VK_RIGHT;
		std::uint32_t ACCEPT = VK_RETURN;
		std::uint32_t BACK = VK_BACK;
	};

	struct MENU_CONTROLLER_BINDS
	{
		std::uint32_t OPEN = eControl::ControlVehicleHorn;
		std::uint32_t OPEN2 = eControl::ControlScriptRB;
		std::uint32_t UP = eControl::ControlFrontendUp;
		std::uint32_t DOWN = eControl::ControlFrontendDown;
		std::uint32_t LEFT = eControl::ControlFrontendLeft;
		std::uint32_t RIGHT = eControl::ControlFrontendRight;
		std::uint32_t ACCEPT = eControl::ControlFrontendAccept;
		std::uint32_t BACK = eControl::ControlFrontendCancel;
	};

	struct PRESSED_KEYS
	{
		bool OPEN = false;
		bool UP = false;
		bool DOWN = false;
		bool LEFT = false;
		bool RIGHT = false;
		bool ACCEPT = false;
		bool BACK = false;
	};

	struct MENU_COLORS
	{
		RGBA mainRect;
		RGBAF mainText;
		RGBA navbarRect;
		RGBAF navbarText;
		RGBA background;
		RGBAF optionText;
		RGBA scroller;
		RGBAF selectedOptionText;
		RGBA footerRect;
		RGBAF footerText;
		RGBA descriptionLine;
		RGBA descriptionRect;
		RGBAF descriptionText;
		RGBA sprites;

		MENU_COLORS()
		{
			mainRect = RGBA(245, 59, 87, 245);
			mainText = RGBAF(210, 218, 226, 255);
			navbarRect = RGBA(15, 15, 15, 245);
			navbarText = RGBAF(210, 218, 226, 255, eFont::FontChaletComprimeCologne);
			background = RGBA(30, 39, 46, 170);
			optionText = RGBAF(210, 218, 226, 255, eFont::FontChaletComprimeCologne);
			scroller = RGBA(210, 218, 226, 235); // 245
			selectedOptionText = RGBAF(30, 39, 46, 255, eFont::FontChaletComprimeCologne);
			footerRect = RGBA(15, 15, 15, 245);
			footerText = RGBAF(210, 218, 226, 255, eFont::FontChaletComprimeCologne);
			descriptionLine = RGBA(255, 255, 255, 245);
			descriptionRect = RGBA(15, 15, 15, 160);
			descriptionText = RGBAF(210, 218, 226, 255, eFont::FontChaletComprimeCologne);
			sprites = RGBA(255, 255, 255, 255);
		}

		void UpdateAlpha(MENU_COLORS defaultColors, float alphaMultiplier)
		{
			mainRect.a = (int)((float)defaultColors.mainRect.a * alphaMultiplier);
			mainText.a = (int)((float)defaultColors.mainText.a * alphaMultiplier);
			navbarRect.a = (int)((float)defaultColors.navbarRect.a * alphaMultiplier);
			mainRect.a = (int)((float)defaultColors.mainRect.a * alphaMultiplier);
			navbarText.a = (int)((float)defaultColors.navbarText.a * alphaMultiplier);
			background.a = (int)((float)defaultColors.background.a * alphaMultiplier);
			optionText.a = (int)((float)defaultColors.optionText.a * alphaMultiplier);
			scroller.a = (int)((float)defaultColors.scroller.a * alphaMultiplier);
			selectedOptionText.a = (int)((float)defaultColors.selectedOptionText.a * alphaMultiplier);
			footerRect.a = (int)((float)defaultColors.footerRect.a * alphaMultiplier);
			footerText.a = (int)((float)defaultColors.footerText.a * alphaMultiplier);
			descriptionLine.a = (int)((float)defaultColors.descriptionLine.a * alphaMultiplier);
			descriptionRect.a = (int)((float)defaultColors.descriptionRect.a * alphaMultiplier);
			descriptionText.a = (int)((float)defaultColors.descriptionText.a * alphaMultiplier);
			sprites.a = (int)((float)defaultColors.sprites.a * alphaMultiplier);
		}
	};
	
	struct MENU_STRUCT
	{
		MENU_BINDS menuBinds; // Binds for keyboard
		MENU_COLORS menuColors;
		MENU_CONTROLLER_BINDS menuControllerBinds; // Binds for controller
	};

	struct Vector2
	{
		float x;
		float y;
	};

	class Vec3
	{
	public:
		Vec3() : p_X(0.f), p_Y(0.f), p_Z(0.f) {}
		Vec3(float x, float y, float z) : p_X(x), p_Y(y), p_Z(z) {}
		Vec3(Vector3 coords) : p_X(coords.x), p_Y(coords.y), p_Z(coords.z) {}

		Vector3 Get() const
		{
			Vector3 vector = { 0.f, 0, 0.f, 0, 0.f, 0 };
			vector.x = p_X;
			vector.y = p_Y;
			vector.z = p_Z;

			return vector;
		}

		const char* getGamezone() const
		{
			return ZONE::GET_NAME_OF_ZONE(this->p_X, this->p_Y, this->p_Z);
		}

		Vec3 operator + (Vec3 vector)
		{
			const auto newX = this->p_X + vector.p_X;
			const auto newY = this->p_Y + vector.p_Y;
			const auto newZ = this->p_Z + vector.p_Z;

			return Vec3(newX, newY, newZ);
		}

		Vec3 operator - (Vec3 vector)
		{
			const auto newX = this->p_X - vector.p_X;
			const auto newY = this->p_Y - vector.p_Y;
			const auto newZ = this->p_Z - vector.p_Z;

			return Vec3(newX, newY, newZ);
		}

		Vec3 operator * (Vec3 vector)
		{
			const auto newX = this->p_X * vector.p_X;
			const auto newY = this->p_Y * vector.p_Y;
			const auto newZ = this->p_Z * vector.p_Z;

			return Vec3(newX, newY, newZ);
		}

		Vec3 operator / (Vec3 vector)
		{
			const auto newX = this->p_X / vector.p_X;
			const auto newY = this->p_Y / vector.p_Y;
			const auto newZ = this->p_Z / vector.p_Z;

			return Vec3(newX, newY, newZ);
		}
	private:
		float p_X = 0.f;
		float p_Y = 0.f;
		float p_Z = 0.f;
	};

	class Vec2
	{
	public:
		Vec2() : p_X(0.f), p_Y(0.f) {}
		Vec2(float x, float y) : p_X(x), p_Y(y) {}

		Vector2 Get() const
		{
			Vector2 newVector = { 0.f, 0.f };
			newVector.x = p_X;
			newVector.y = p_Y;

			return newVector;
		}

		Vec2 operator + (Vec2 vector)
		{
			const auto newX = this->p_X + vector.p_X;
			const auto newY = this->p_Y + vector.p_Y;

			return Vec2(newX, newY);
		}

		Vec2 operator - (Vec2 vector)
		{
			const auto newX = this->p_X - vector.p_X;
			const auto newY = this->p_Y - vector.p_Y;

			return Vec2(newX, newY);
		}

		Vec2 operator * (Vec2 vector)
		{
			const auto newX = this->p_X * vector.p_X;
			const auto newY = this->p_Y * vector.p_Y;

			return Vec2(newX, newY);
		}

		Vec2 operator / (Vec2 vector)
		{
			const auto newX = this->p_X / vector.p_X;
			const auto newY = this->p_Y / vector.p_Y;

			return Vec2(newX, newY);
		}
	private:
		float p_X = 0.f;
		float p_Y = 0.f;
	};
};