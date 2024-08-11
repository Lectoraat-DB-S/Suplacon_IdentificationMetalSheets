#ifndef TESTSCRIPT_SETTINGS_H
#define TESTSCRIPT_SETTINGS_H

#define RUN_PERFORMANCE_TESTS true
#define RUN_UNITTESTS false
#if RUN_UNITTESTS
#define TEST_IMAGEPREPPER true
#endif

#include <string>

#include "HalconCpp.h"

#include "Fotoanalyses_Settings.h"

const std::string expectedNumbers[MAX_PHOTOCOUNT] = {
	"1963896001", "1963500001", "1936814007",
	"1966566004", "1966580001", "1966520002",
	"1966520005", "1966558005", "1966558003",
	"1966558008", "1966558003", "1966558004",
	"1966558007", "1966558009", "1966558010",
	"1966558006", "1966558005", "1966566003",
	"1966566002", "1966518018", "1966518005",
	"1966518001" };

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