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