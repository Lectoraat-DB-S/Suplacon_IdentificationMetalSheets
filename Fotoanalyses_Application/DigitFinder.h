#ifndef DIGITFINDER_H
#define DIGITFINDER_H

#define SIGMA 5
#define PERCENT 99.5

#define MIN_AREA_DIGIT 150
#define MAX_AREA_DIGIT 99999
#define MIN_SIZE_DIGIT 18
#define MAX_SIZE_DIGIT 70
#define SIZE_MULTIPLIER 2

#include "HalconCpp.h"

class DigitFinder
{
private:
	HalconCpp::HImage image{};
	HalconCpp::HRegion outlineDigits{};

public:
	DigitFinder();
	DigitFinder(HalconCpp::HImage image);

	bool execute();
	bool execute(HalconCpp::HImage image);
	void print();

	HalconCpp::HRegion getOutlineDigits() { return outlineDigits; };

};

#endif

