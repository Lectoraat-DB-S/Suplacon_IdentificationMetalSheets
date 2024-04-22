//Finding possible numbers
#include "FindDigits.h"

using namespace HalconCpp;

FindDigits::FindDigits()
{
	//Do nothing
}

FindDigits::FindDigits(HImage image)
{
	this->image = image;
}

bool FindDigits::execute()
{
	HRegion darkRegions = image.VarThreshold(FINDER_MASK_SIZE, FINDER_MASK_SIZE, STD_DEV_SCALE, ABS_THRESHOLD, "dark");
	darkRegions = darkRegions.Connection();

	outlineDigits = darkRegions.SelectShape("area", "and", MIN_AREA_DIGIT, MAX_AREA_DIGIT);
	outlineDigits = outlineDigits.SelectShape("width", "and", MIN_SIZE_DIGIT, MAX_SIZE_DIGIT);
	outlineDigits = outlineDigits.SelectShape("height", "and", MIN_SIZE_DIGIT, MAX_SIZE_DIGIT);

	outlineDigits = outlineDigits.SortRegion("first_point", "true", "column");

	return true;
}

bool FindDigits::execute(HImage image)
{
	this->image = image;
	
	return execute();
}

void FindDigits::print()
{
	Hlong digitCount = outlineDigits.CountObj();
	std::cout << "A total of " << digitCount << " digits have been found!\n";
}

