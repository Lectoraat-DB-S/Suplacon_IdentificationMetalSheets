#include "Testscript_Settings.h"

using namespace HalconCpp;

PerformanceTester::PerformanceTester(DigitIdentifier* currentIdentifier, BYTE* currentPhotocount)
{
	this->currentIdentifier = currentIdentifier;
	this->currentPhotocount = currentPhotocount;
}

void PerformanceTester::nextStepTest(ApplicationStatus* currentStatus)
{
	if (*currentStatus == WaitingForInput)
	{
		std::cout << "Collecting Performance Data...\n";
		HImage image = currentIdentifier->getImage();
		HRegion outlineDigits = currentIdentifier->getOutlineDigits();
		foundNumbers[*currentPhotocount - 1] = currentIdentifier->GetFoundNumber();

		std::cout << "Exporting Performance Data...\n";
		outlineDigits = outlineDigits.DilationCircle(2.5);
		image = image.PaintRegion(outlineDigits, 0.0, "fill");
		image.WriteImage("png", 255, std::to_string((int)* currentPhotocount).c_str());

		*currentStatus = AquiringImage;
	}
	else if (*currentStatus == None)
	{
		std::string expectedNumbers[] = NUMBERS_ON_TESTPHOTOS;
		bool areReadingsCorrect[MAX_PHOTOCOUNT];
		BYTE correctReadingCounter = 0;

		std::cout << "---Results Performance Test---\n\n";
		std::cout << "Testname: \'Determining Correctness of Readings\'\n";
		for (UINT16 i = 1; i <= MAX_PHOTOCOUNT; i++)
		{
			bool isReadingsCorrect = (expectedNumbers[i - 1] == foundNumbers[i - 1]);

			if (isReadingsCorrect)
				correctReadingCounter++;

			std::cout << "Photo ID: " << i
				<< ", Expected: " << expectedNumbers[i - 1]
				<< ", Found: " << foundNumbers[i - 1]
				<< ", Is Match? " << (isReadingsCorrect ? "YES" : "NO")
				<< "\n";
		}

		std::cout << (correctReadingCounter * 100 / MAX_PHOTOCOUNT) << "% of readings is correct!\n\n";
		std::cout << "---End Performance Test---\n";
	}
	else
	{
		//Do nothing
	}
}


Unittester::Unittester(BYTE* currentPhotocount)
{
	this->currentPhotocount = currentPhotocount;
}

void Unittester::nextStepTest(ApplicationStatus* currentStatus, HalconCpp::HImage currentImage, ImagePrepper* imagePrepper)
{
	if (*currentStatus == WaitingForInput)
		*currentStatus = AquiringImage;
	else if (*currentStatus == PreppingImage)
	{
		std::cout << "Collecting Original Image...\n";
		currentImage.InvertImage().WriteImage("png", 255, std::to_string((int)(* currentPhotocount) * 2 - 1).c_str());
	}
	else if (*currentStatus == FindingDigits)
	{
		std::cout << "Collecting Prepped Image...\n";
		imagePrepper->getImage().WriteImage("png", 255, std::to_string((int)(*currentPhotocount) * 2).c_str());
	}
	else if (*currentStatus == None)
	{
		std::cout << "---Results Unittest---\n\n";
		std::cout << "Testname: \'Validation ImagePrepper'\n";
		std::cout << "Manual review of the photosets is required!\n";
		std::cout << "Photoset ID's\n";
		for (UINT16 i = 1; i <= MAX_PHOTOCOUNT * 2; i += 2)
		{
			std::cout << "Set " << (i - 1)/2 + 1 << " : " << i << " & " << i + 1 << "\n";
		}

		std::cout << "\n---End Unittest---\n";
	}
	else
	{
		//Do nothing
	}
}