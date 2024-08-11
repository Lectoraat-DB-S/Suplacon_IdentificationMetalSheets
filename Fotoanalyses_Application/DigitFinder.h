#ifndef DIGITFINDER_H
#define DIGITFINDER_H

//The following macros are used to configure the DigitFinder class.
#define SIGMA 5 //Sigma for the Gaussian smoothing of the input image
#define PERCENT 99.5 //Percentage for the gray value difference on the input image
#define MIN_AREA_DIGIT 150
#define MAX_AREA_DIGIT 99999
#define MIN_SIZE_DIGIT 18
#define MAX_SIZE_DIGIT 70
#define SIZE_MULTIPLIER 2

#include "HalconCpp.h"

//This class is used to collect the outlines of all digits on a given image.
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

