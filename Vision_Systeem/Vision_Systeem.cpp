// Vision_Systeem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define PHOTO_NAME "Fotos_Plaatcodes/4.jpg"

#include <iostream>

#include "HalconCpp.h"

using namespace std;
using namespace HalconCpp;

int main()
{
	//Collecting image
	HFramegrabber camera = HFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", PHOTO_NAME, "default", 1, -1);
	camera.GrabImageStart(-1);
	HImage image = camera.GrabImageAsync(-1);
	camera.CloseFramegrabber();

	//Preprocessing image
	image = image.ZoomImageFactor(0.25, 0.25, "constant");
	image = image.Rgb1ToGray();
	image = image.GrayRangeRect(5, 5);
	
	Hlong width, height;
	image.GetImageSize(&width, &height);
	image = image.Emphasize(width, height, 2);

	image = image.InvertImage();

	//Finding possible numbers
	HRegion darkRegions = image.VarThreshold(15, 15, 0.2, 2, "dark");
	HRegion outlineNumbers = darkRegions.Connection();

	outlineNumbers = outlineNumbers.SelectShape("area", "and", 450, 900);
	outlineNumbers = outlineNumbers.SelectShape("width", "and", 0, 60);
	outlineNumbers = outlineNumbers.SelectShape("height", "and", 0, 60);
	outlineNumbers = outlineNumbers.SortRegion("first_point", "true", "column");

	//Identifying/Reading numbers
	HOCRMlp classifier = HOCRMlp("Industrial_0-9_NoRej");
	HTuple foundNumbers{}, confidences{};

	Hlong numbersCount = outlineNumbers.CountObj();
	for (byte i = 0; i < numbersCount; i++)
	{
		HRegion outlineNumber = outlineNumbers.SelectObj(i + (byte)1);

		double confidence;
		HString foundNumber = classifier.DoOcrSingleClassMlp(outlineNumber, image, 1, &confidence);

		confidences.Append(confidence);
		foundNumbers.Append(foundNumber);
	}

	//Display found numbers
	HTuple row, column;
	HTuple area = outlineNumbers.AreaCenter(&row, &column);

	for (byte i = 0; i < numbersCount; i++)
	{
		double shortConfidence = round(confidences[i].D() * 1000) / 1000;
		cout << "Number: " << foundNumbers[i].S().Text() << ", X/Y: " << row[i].D() << "/" << column[i].D() << ", Confidence: " << shortConfidence << "\n";
	}

	cin.get();

}

