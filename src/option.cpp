#include "option.hpp"

BEGIN_SOURCE_NS
Option::Option(std::string optionText,
	std::string optionRightText,
	std::string optionDescription,
	std::function<void()> optionCallback,
	int* optionInteger,
	int Imin, int Imax, int Istep,
	float* optionFloat,
	float Fmin, float Fmax, float Fstep,
	bool* optionBoolean,
	std::vector<std::string>* optionStringVector,
	std::string optionSubmenu)
{
	this->p_optionLeftText = optionText;
	this->p_optionRightText = optionRightText;
	this->p_optionDescription = optionDescription;
	this->p_optionFunction = optionCallback;
	this->p_optionInteger = optionInteger;
	this->p_optionIntegerMin = Imin;
	this->p_optionIntegerMax = Imax;
	this->p_optionIntegerStep = Istep;
	this->p_optionFloat = optionFloat;
	this->p_optionFloatMin = Fmin;
	this->p_optionFloatMax = Fmax;
	this->p_optionFloatStep = Fstep;
	this->p_optionBoolean = optionBoolean;
	this->p_optionStringVector = optionStringVector;
	this->p_optionSubmenu = optionSubmenu;
	this->p_optionType = "null";
	this->p_optionSliderType = Enums::SLIDER_TYPE::NONE;
}

void Option::setLeftText(std::string newText) const
{
	this->p_optionLeftText = newText;
}

void Option::setRightText(std::string newText) const
{
	this->p_optionRightText = newText;
}

void Option::setDescription(std::string newText) const
{
	this->p_optionDescription = newText;
}

void Option::setOptionType(std::string newType) const
{
	this->p_optionType = newType;
}

void Option::setFunction(std::function<void()> newFunction) const
{
	this->p_optionFunction = newFunction;
}

void Option::setBooleanValue(bool newValue) const
{
	*this->p_optionBoolean = newValue;
}

	void Option::setStringVectorValue(std::vector<std::string> newValue) const
{
	*this->p_optionStringVector = newValue;
}

void Option::setSliderType(Enums::SLIDER_TYPE type) const
{
	this->p_optionSliderType = type;
}

void Option::setIntegerValue(int newValue) const
{
	*this->p_optionInteger = newValue;
}

void Option::setFloatValue(float newValue) const
{
	*this->p_optionFloat = newValue;
}

const std::string Option::getLeftText() const
{
	return this->p_optionLeftText;
}

const std::string Option::getRightText() const
{
	return this->p_optionRightText;
}

const std::string Option::getDescription() const
{
	return this->p_optionDescription;
}

const std::string Option::getOptionType() const
{
	return this->p_optionType;
}

const void Option::useFunction() const
{
	this->p_optionFunction();
}

const bool Option::getBooleanValue() const
{
	return *this->p_optionBoolean;
}

const std::string Option::getVectorValue(std::uint32_t index) const
{
	return this->p_optionStringVector->at((std::size_t)index);
}

const Enums::SLIDER_TYPE Option::getSliderType() const
{
	return this->p_optionSliderType;
}

const std::string Option::getSubmenu() const
{
	return this->p_optionSubmenu;
}

const int* Option::getIntegerAddress() const
{
	return this->p_optionInteger;
}

const int Option::getIntegerMin() const
{
	return this->p_optionIntegerMin;
}

const int Option::getIntegerMax() const
{
	return this->p_optionIntegerMax;
}

const int Option::getIntegerStep() const
{
	return this->p_optionIntegerStep;
}

const float* Option::getFloatAddress() const
{
	return this->p_optionFloat;
}

const float Option::getFloatMin() const
{
	return this->p_optionFloatMin;
}

const float Option::getFloatMax() const
{
	return this->p_optionFloatMax;
}

const float Option::getFloatStep() const
{
	return this->p_optionFloatStep;
}

END_SOURCE_NS