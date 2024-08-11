#include "DigitIdentifier.h"

using namespace HalconCpp;

DigitIdentifier::DigitIdentifier()
{
	this->maxDigitCount = MIN_DIGITS;
}

DigitIdentifier::DigitIdentifier(const char* fontName)
{
	this->classifier = HOCRMlp(fontName);
	this->maxDigitCount = MIN_DIGITS;
}

DigitIdentifier::DigitIdentifier(HImage image, HRegion outlineNumbers, const char* fontName)
{
	this->image = image;
	this->outlineDigits = outlineNumbers;
	this->classifier = HOCRMlp(fontName);

	UINT16 digitCount = (UINT16) outlineDigits.CountObj();
	if (digitCount > MAX_DIGITS)
		this->maxDigitCount = MAX_DIGITS;
	else
		this->maxDigitCount = digitCount;
}

bool DigitIdentifier::execute()
{
	HTuple row{}, column{};
	HTuple area = outlineDigits.AreaCenter(&row, &column);

	for (int i = MIN_DIGITS; i < maxDigitCount; i++)
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

bool DigitIdentifier::execute(HImage image, HRegion outlineNumbers)
{
	this->image = image;
	this->outlineDigits = outlineNumbers;

	UINT16 digitCount = (UINT16) outlineDigits.CountObj();
	if (digitCount > MAX_DIGITS)
		this->maxDigitCount = MAX_DIGITS;
	else
		this->maxDigitCount = digitCount;
	
	return execute();
}

std::string DigitIdentifier::GetFoundNumber() {
	std::string foundNumber = "";

	for (BYTE i = MIN_DIGITS; i < maxDigitCount; i++)
		foundNumber.append(foundDigits[i].value);

	if (MAX_DIGITS != maxDigitCount)
	{
		BYTE difference = MAX_DIGITS - maxDigitCount;
		for (byte i = MIN_DIGITS; i < difference; i++)
			foundNumber.append(TOKEN_MISSING_DIGIT);
	}

	return foundNumber;
}

void DigitIdentifier::print()
{
	std::cout << "--V The first " << maxDigitCount << " digits have been printed. V--\n";
	for (BYTE i = MIN_DIGITS; i < maxDigitCount; i++)
	{
		double shortConfidence = round(foundDigits[i].confidence * 1000) / 1000;
		std::cout << "Digit: " << foundDigits[i].value << ", X/Y: " << foundDigits[i].row << "/" << foundDigits[i].column << ", Confidence: " << shortConfidence << "\n";
	}
}





