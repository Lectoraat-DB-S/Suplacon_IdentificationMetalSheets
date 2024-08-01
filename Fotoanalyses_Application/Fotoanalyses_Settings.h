#ifndef FOTOANALYSES_SETTINGS_H
#define FOTOANALYSES_SETTINGS_H

#define USING_CAMERA false
#if USING_CAMERA
#define SAVING_PHOTOS true
#define INTERFACE_NAME "GigEVision2"
#define RESOLUTION 0
#define FIELD "progressive"
#define PHOTOSROOT "default"
#define DEVICE_NAME "0030534b6f89_Basler_acA128060gm"
#define PORT 0
#else
#define IS_GRAYSCALE true
#define INTERFACE_NAME "File"
#define RESOLUTION 1
#define FIELD "default"
#define PHOTOSROOT "../Dataset_Plaatcodes"
#define DEVICE_NAME "default"
#define PORT 1
#endif


#define MAX_PHOTOCOUNT 22
#define MAX_DELAY 99.9
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