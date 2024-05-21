#ifndef TESTSCRIPT_SETTINGS_H
#define TESTSCRIPT_SETTINGS_H

#define RUN_PERFORMANCE_TESTS true
//#define RUN_FUNCTIONAL_TESTS false
//#define RUN_UNITTESTS false

//#define TESTRESULTS_ROOT "../Testresults"
//#define PERFORMANCE_RESULTS_LOCATION "/Performance"

#define NUMBERS_ON_TESTPHOTOS {"1963814007", "1963814005"} 

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


//ApplicationStatus StepFunctionalTest();
//ApplicationStatus StepUnittest();


#endif