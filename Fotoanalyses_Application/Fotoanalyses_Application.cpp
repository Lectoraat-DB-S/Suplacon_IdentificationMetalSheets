#define PHOTOSROOT "Fotos_Plaatcodes"
#define MAX_PHOTOCOUNT 7
#define AQUISITION_DELAY
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
	HFramegrabber camera = HFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", PHOTOSROOT, "default", 1, -1);
	camera.GrabImageStart(-1);

	PrepImage prepper = PrepImage();
	FindDigits finder = FindDigits();
	IdentifyDigits identifier = IdentifyDigits(OCR_FONT_NAME);

	byte photocounter = 0;
	while (photocounter < MAX_PHOTOCOUNT)
	{
		HImage image = camera.GrabImageAsync(-1);
		cout << "New image acquired!\n";

		prepper.execute(image);
		prepper.print();
		HImage preppedImage = prepper.getImage();

		finder.execute(preppedImage);
		finder.print();
		HRegion outlineDigits = finder.getOutlineDigits();

		identifier.execute(preppedImage, outlineDigits);
		identifier.print();
		FoundDigit* numbers = identifier.getFoundDigits();
		
		//Do something with 'numbers'

		photocounter++;
	}
	
	camera.CloseFramegrabber();

}

