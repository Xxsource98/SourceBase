#pragma once
#include <Windows.h>
#include <iostream>
#include <functional>
#include "structs.hpp"
#include "constVariables.hpp"

namespace Source {
	class Option
	{
	public:
		/*I don't know if texts in game has any limitations, but description won't display big strings (I don't really know why)*/
		Option(std::string optionText,
			std::string optionRightText = "",
			std::string optionDescription = "",
			std::function<void()> optionCallback = [] {},
			int* optionInteger = nullptr,
			int Imin = 0, int Imax = 0, int Istep = 1,
			float* optionFloat = nullptr,
			float Fmin = 0.f, float Fmax = 0.f, float Fstep = 0.1f,
			bool* optionBoolean = 0,
			std::vector<std::string>* optionStringVector = {},
			std::string optionSubmenu = "");

		void setLeftText(std::string newText) const;
		void setRightText(std::string newText) const;
		void setDescription(std::string newText) const;
		void setOptionType(std::string newType) const;
		void setFunction(std::function<void()> newFunction) const;
		void setBooleanValue(bool newValue) const;
		void setStringVectorValue(std::vector<std::string> newValue) const;
		void setSliderType(Enums::SLIDER_TYPE type) const;
		void setIntegerValue(int newValue) const;
		void setFloatValue(float newValue) const;

		const std::string getLeftText() const;
		const std::string getRightText() const;
		const std::string getDescription() const;
		const std::string getOptionType() const;
		const void useFunction() const;
		const std::string getVectorValue(std::uint32_t index) const;
		const Enums::SLIDER_TYPE getSliderType() const;
		const std::string getSubmenu() const;
		const bool getBooleanValue() const;
		const int* getIntegerAddress() const;
		const int getIntegerMin() const;
		const int getIntegerMax() const;
		const int getIntegerStep() const;
		const float* getFloatAddress() const;
		const float getFloatMin() const;
		const float getFloatMax() const;
		const float getFloatStep() const;

	private:
		mutable std::string p_optionLeftText;
		mutable std::string p_optionRightText;
		mutable std::string p_optionDescription;
		mutable std::string p_optionSubmenu;
		mutable std::string p_optionType;
		mutable std::function<void()> p_optionFunction;
		mutable Enums::SLIDER_TYPE p_optionSliderType;
		mutable std::vector<std::string>* p_optionStringVector;
		mutable int* p_optionInteger;
		mutable int p_optionIntegerMin;
		mutable int p_optionIntegerMax;
		mutable int p_optionIntegerStep;
		mutable float* p_optionFloat;
		mutable float p_optionFloatMax;
		mutable float p_optionFloatMin;
		mutable float p_optionFloatStep;
		mutable bool* p_optionBoolean;
		mutable int* p_vectorInteger;
	};
}