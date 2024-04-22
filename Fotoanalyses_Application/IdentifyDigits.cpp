//Identifying/Reading numbers

#include "IdentifyDigits.h"

using namespace HalconCpp;

IdentifyDigits::IdentifyDigits(const char* fontName)
{
	this->classifier = HOCRMlp(fontName);
}

IdentifyDigits::IdentifyDigits(HImage image, HRegion outlineNumbers, const char* fontName)
{
	this->image = image;
	this->outlineDigits = outlineNumbers;
	this->classifier = HOCRMlp(fontName);
}

bool IdentifyDigits::execute()
{
	HTuple row{}, column{};
	HTuple area = outlineDigits.AreaCenter(&row, &column);

	Hlong digitCount = outlineDigits.CountObj();
	if (digitCount > MAX_DIGITS)
		digitCount = MAX_DIGITS;

	for (int i = MIN_DIGITS; i < digitCount; i++)
	{
		HRegion outlineDigit = outlineDigits.SelectObj(i + 1);

		double confidence{};
		HString foundDigit = classifier.DoOcrSingleClassMlp(outlineDigit, image, 1, &confidence);

		if (i < MAX_DIGITS)
		{
			foundDigits[i].value = foundDigit.Text();
			foundDigits[i].confidence = confidence;
			foundDigits[i].row = row[i].D();
			foundDigits[i].column = column[i].D();
		}
	}

	return true;
}

bool IdentifyDigits::execute(HImage image, HRegion outlineNumbers)
{
	this->image = image;
	this->outlineDigits = outlineNumbers;

	return execute();
}

void IdentifyDigits::print()
{
	Hlong digitCount = outlineDigits.CountObj();
	if (digitCount > MAX_DIGITS)
		digitCount = MAX_DIGITS;

	std::cout << "--V The following " << digitCount << " digits have been found. V--\n";
	for (byte i = 0; i < digitCount; i++)
	{
		double shortConfidence = round(foundDigits[i].confidence * 1000) / 1000;
		std::cout << "Digit: " << foundDigits[i].value << ", X/Y: " << foundDigits[i].row << "/" << foundDigits[i].column << ", Confidence: " << shortConfidence << "\n";
	}
}





