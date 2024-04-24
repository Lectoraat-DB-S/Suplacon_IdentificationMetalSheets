#ifndef IDENTIFY_DIGITS_H
#define IDENTIFY_DIGITS_H

#define MIN_DIGITS 0
#define MAX_DIGITS 10

#include <string>

#include "HalconCpp.h"

struct Digit {
	std::string value{};
	double confidence{};
	double row{};
	double column{};
};

class DigitIdentifier
{

private:
	HalconCpp::HImage image;
	HalconCpp::HRegion outlineDigits;
	HalconCpp::HOCRMlp classifier;
	Digit foundDigits[MAX_DIGITS];

public:
	DigitIdentifier(const char* fontName);
	DigitIdentifier(HalconCpp::HImage image, HalconCpp::HRegion outlineDigits, const char* fontName);

	bool execute();
	bool execute(HalconCpp::HImage image, HalconCpp::HRegion outlineDigits);
	void print();

	Digit* getFoundDigits() { return foundDigits; };
};

#endif
