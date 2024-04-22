#define PHOTO_NAME "Fotos_Plaatcodes/1.jpg" //"Fotos_Plaatcodes/4.jpg"
#define OCR_FONT_NAME "Industrial_0-9_NoRej"

#include <iostream>

#include "HalconCpp.h"

#include "PrepImage.h"
#include "FindDigits.h"
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

	FindDigits finder = FindDigits(preppedImage);
	finder.execute();
	finder.print();
	HRegion outlineDigits = finder.getOutlineDigits();

	IdentifyDigits identifier = IdentifyDigits(preppedImage, outlineDigits, OCR_FONT_NAME);
	identifier.execute();
	identifier.print();
	//FoundDigit* numbers = identifier.getFoundDigits();

	//cout << numbers[1].row;

	cin.get();

}

