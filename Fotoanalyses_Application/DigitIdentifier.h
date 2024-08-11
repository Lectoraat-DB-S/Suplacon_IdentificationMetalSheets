#ifndef DIGITIDENTIFIER_H
#define DIGITIDENTIFIER_H

//The following macros are used to configure the DigitIdentifier class.
#define MIN_DIGITS 0 //Minimum amount of digits of a programnumber
#define MAX_DIGITS 10 //Maximum amount of digits of a programnumber
#define TOKEN_MISSING_DIGIT "?" //If a DigitIdentifier object receives less than the maximum amount of digits, then the value of each missing digit will be set to this token value.

#include <string>
#include "HalconCpp.h"

//This struct stores information about a identified digit.
struct Digit {
	std::string value{};
	double confidence{};
	double row{};
	double column{};
};

//This class is used to convert outlines of digits to a programnumber.
class DigitIdentifier
{
private:
	HalconCpp::HImage image;
	HalconCpp::HRegion outlineDigits;
	UINT16 maxDigitCount;
	HalconCpp::HOCRMlp classifier;
	Digit foundDigits[MAX_DIGITS];

public:
	DigitIdentifier();
	DigitIdentifier(const char* fontName);
	DigitIdentifier(HalconCpp::HImage image, HalconCpp::HRegion outlineDigits, const char* fontName);

	bool execute();
	bool execute(HalconCpp::HImage image, HalconCpp::HRegion outlineDigits);
	std::string GetFoundNumber();
	void print();

	void setFontName(const char* fontName) { this->classifier = HalconCpp::HOCRMlp(fontName); }
	HalconCpp::HImage getImage() { return image; };
	HalconCpp::HRegion getOutlineDigits() { return outlineDigits; };
	Digit* getFoundDigits() { return foundDigits; };
};

#endif

