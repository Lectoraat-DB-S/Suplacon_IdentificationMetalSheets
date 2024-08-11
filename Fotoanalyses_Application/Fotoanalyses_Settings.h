#ifndef FOTOANALYSES_SETTINGS_H
#define FOTOANALYSES_SETTINGS_H

//The following macros are used to configure the fotoanalyses part of the application.
#define USING_CAMERA false
#if USING_CAMERA
#define SAVING_PHOTOS true
#define INTERFACE_NAME "GigEVision2" //HALCON image acquisition interface name, i.e., name of the corresponding DLL (Windows)
#define RESOLUTION 0 //Desired resolution of image acquisition interface
#define FIELD "progressive" //Desired half image or full image
#define PHOTOSROOT "default" //Location of the input images
#define DEVICE_NAME "0030534b6f89_Basler_acA128060gm" //Device the image acquisition device is connected to
#define PORT 0 //Port the image acquisition device is connected to
#else
#define IS_GRAYSCALE true //Are the input images in grayscale?
#define INTERFACE_NAME "File" //HALCON image acquisition interface name, i.e., name of the corresponding DLL (Windows)
#define RESOLUTION 1 //Desired resolution of image acquisition interface
#define FIELD "default" //Desired half image or full image
#define PHOTOSROOT "../Dataset_Plaatcodes/Fotos_Camera" //Location of the input images
#define DEVICE_NAME "default" //Device the image acquisition device is connected to
#define PORT 1 //Port the image acquisition device is connected to
#endif

#define MAX_PHOTOCOUNT 22 //Maximum amount of photos to take
#define MAX_DELAY 99.9 //Maximum tolerated delay between the start of the asynchronous image grab and the delivery of the image [ms]
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