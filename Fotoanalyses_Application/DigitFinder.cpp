//Finding possible numbers
#include "DigitFinder.h"

using namespace HalconCpp;

DigitFinder::DigitFinder()
{
	//Do nothing
}

DigitFinder::DigitFinder(HImage image)
{
	this->image = image;
}

bool DigitFinder::execute()
{
	HRegion darkRegions = image.VarThreshold(FINDER_MASK_SIZE, FINDER_MASK_SIZE, STD_DEV_SCALE, ABS_THRESHOLD, "dark");
	darkRegions = darkRegions.Connection();

	outlineDigits = darkRegions.SelectShape("area", "and", MIN_AREA_DIGIT, MAX_AREA_DIGIT);
	outlineDigits = outlineDigits.SelectShape("width", "and", MIN_SIZE_DIGIT, MAX_SIZE_DIGIT);
	outlineDigits = outlineDigits.SelectShape("height", "and", MIN_SIZE_DIGIT, MAX_SIZE_DIGIT);

	outlineDigits = outlineDigits.SortRegion("first_point", "true", "column");

	return true;
}

bool DigitFinder::execute(HImage image)
{
	this->image = image;
	
	return execute();
}

void DigitFinder::print()
{
	Hlong digitCount = outlineDigits.CountObj();
	std::cout << "A total of " << digitCount << " digits have been found!\n";
}

