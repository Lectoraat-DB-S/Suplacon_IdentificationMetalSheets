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
	Hlong threshold = 0;
	HRegion darkRegions = image.CharThreshold(image, 5, 99.5, &threshold);
	darkRegions = darkRegions.Connection();

	darkRegions = darkRegions.SelectShape("area", "and", MIN_AREA_DIGIT, MAX_AREA_DIGIT);
	darkRegions = darkRegions.SelectShape("width", "and", MIN_SIZE_DIGIT, MAX_SIZE_DIGIT);
	//darkRegions = darkRegions.SelectShape("height", "and", MIN_SIZE_DIGIT * 2, MAX_SIZE_DIGIT * 2);

	darkRegions = darkRegions.SortRegion("first_point", "true", "column");
	outlineDigits = darkRegions;

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

