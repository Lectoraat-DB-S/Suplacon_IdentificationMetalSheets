// Vision_Systeem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define PHOTO_NAME "Fotos_Plaatcodes/2.jpg" //"Fotos_Plaatcodes/4.jpg"

#include <iostream>

#include "HalconCpp.h"

#include "PrepImage.h"
#include "IdentifyDigits.h"

using namespace std;
using namespace HalconCpp;

int main()
{
	//Collecting image
	HFramegrabber camera = HFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", PHOTO_NAME, "default", 1, -1);
	camera.GrabImageStart(-1);
	HImage image = camera.GrabImageAsync(-1);
	camera.CloseFramegrabber();

	PrepImage prepper = PrepImage(image);
	prepper.execute();
	prepper.print();
	HImage preppedImage = prepper.getImage();


	//Finding possible numbers
	HRegion darkRegions = preppedImage.VarThreshold(15, 15, 0.2, 2, "dark");
	HRegion outlineNumbers = darkRegions.Connection();

	outlineNumbers = outlineNumbers.SelectShape("area", "and", 450, 900);
	outlineNumbers = outlineNumbers.SelectShape("width", "and", 0, 60);
	outlineNumbers = outlineNumbers.SelectShape("height", "and", 0, 60);
	outlineNumbers = outlineNumbers.SortRegion("first_point", "true", "column");


	IdentifyDigits identifier = IdentifyDigits(preppedImage, outlineNumbers, "Industrial_0-9_NoRej");
	identifier.execute();
	identifier.print();

	//FoundDigit* numbers = identifier.getFoundDigits();
	//cout << numbers[1].row;

	cin.get();

}

