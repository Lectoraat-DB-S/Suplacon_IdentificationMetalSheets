#ifndef TESTSCRIPT_SETTINGS_H
#define TESTSCRIPT_SETTINGS_H

//#define TESTRESULTS_ROOT "../Testresults"

#define RUN_PERFORMANCE_TESTS false
#define NUMBERS_ON_TESTPHOTOS {"1963814007", "1963814005"} 
//#define PERFORMANCE_RESULTS_LOCATION "/Performance"

#define RUN_UNITTESTS true
#define TEST_IMAGEPREPPER true

//#define RUN_FUNCTIONAL_TESTS false

#include <string>

#include "HalconCpp.h"

#include "Fotoanalyses_Settings.h"

class PerformanceTester
{
private:
	DigitIdentifier* currentIdentifier;
	BYTE* currentPhotocount;
	std::string foundNumbers[MAX_PHOTOCOUNT];

public:
	PerformanceTester(DigitIdentifier* currentIdentifier, BYTE* currentPhotocount);
	void nextStepTest(ApplicationStatus* currentStatus);
};

class Unittester
{
private:
	BYTE* currentPhotocount;

public:
	Unittester(BYTE* currentPhotocount);
	void nextStepTest(ApplicationStatus* currentStatus, HalconCpp::HImage currentImage, ImagePrepper* imagePrepper);
};


//ApplicationStatus StepFunctionalTest();
//ApplicationStatus StepUnittest();


#endif