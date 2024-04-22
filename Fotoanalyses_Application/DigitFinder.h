#ifndef FIND_DIGITS_H
#define FIND_DIGITS_H

#define FINDER_MASK_SIZE 15
#define STD_DEV_SCALE 0.2
#define ABS_THRESHOLD 2

#define MIN_AREA_DIGIT 450
#define MAX_AREA_DIGIT 900
#define MIN_SIZE_DIGIT 0
#define MAX_SIZE_DIGIT 60

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

