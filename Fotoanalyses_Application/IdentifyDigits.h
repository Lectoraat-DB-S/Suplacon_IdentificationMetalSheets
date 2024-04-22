#ifndef IDENTIFY_DIGITS_H
#define IDENTIFY_DIGITS_H

#define MIN_DIGITS 0
#define MAX_DIGITS 10

#include <string>

#include "HalconCpp.h"

struct FoundDigit {
	std::string value{};
	double confidence{};
	double row{};
	double column{};
};

class IdentifyDigits
{

private:
	HalconCpp::HImage image;
	HalconCpp::HRegion outlineDigits;
	HalconCpp::HOCRMlp classifier;
	FoundDigit foundDigits[MAX_DIGITS];

public:
	IdentifyDigits(const char* fontName);
	IdentifyDigits(HalconCpp::HImage image, HalconCpp::HRegion outlineDigits, const char* fontName);

	bool execute();
	bool execute(HalconCpp::HImage image, HalconCpp::HRegion outlineDigits);
	void print();

	FoundDigit* getFoundDigits() { return foundDigits; };
};

#endif

