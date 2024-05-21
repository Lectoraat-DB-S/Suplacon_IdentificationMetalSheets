#ifndef FOTOANALYSES_SETTINGS_H
#define FOTOANALYSES_SETTINGS_H

#define PHOTOSROOT "../Testfotos_Plaatcodes"
#define MAX_PHOTOCOUNT 2//7
#define OCR_FONT_NAME "Industrial_0-9_NoRej"

#include <iomanip>
#include <iostream>

#include "HalconCpp.h"
#include "open62541pp/open62541pp.h"

#include "ImagePrepper.h"
#include "DigitFinder.h"
#include "DigitIdentifier.h"

#include "OPC_UA_Settings.h"

enum ApplicationStatus
{
	None,
	InitializingObjects,
	ConnectingToServer,
	WritingToNode,
	StartingImageAquisition,
	AquiringImage,
	EndingImageAquisition,
	PreppingImage,
	FindingDigits,
	IdentifyingDigits,
	WaitingForInput
};

#endif