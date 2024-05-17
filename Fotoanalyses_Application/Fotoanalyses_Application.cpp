#define PHOTOSROOT "Fotos_Plaatcodes"
#define MAX_PHOTOCOUNT 7
#define OCR_FONT_NAME "Industrial_0-9_NoRej"

#include <iomanip>
#include <iostream>

#include "HalconCpp.h"
#include "open62541pp/open62541pp.h"

#include "ImagePrepper.h"
#include "DigitFinder.h"
#include "DigitIdentifier.h"

using namespace std;
using namespace HalconCpp;

int main()
{
	HFramegrabber camera = HFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", PHOTOSROOT, "default", 1, -1);
	camera.GrabImageStart(-1);

	ImagePrepper prepper = ImagePrepper();
	DigitFinder finder = DigitFinder();
	DigitIdentifier identifier = DigitIdentifier(OCR_FONT_NAME);

	opcua::Client client;
	client.connect(URL_OPCUA_SERVER);

	auto nodeAnswer = client.getRootNode().browseChild({ {0, "Objects"}, {1, "TheAnswer"} });
	std::cout << "Node Name: \"" << nodeAnswer.readDisplayName().getText() << "\"\n";
	std::cout << "Node ID: (" << nodeAnswer.getNodeId().toString() << ")\n";
	std::cout << "Node Value: [" << nodeAnswer.readDataValue().getValue().getScalarCopy<std::string>() << "]\n";

	BYTE photocounter = 0;
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
		Digit* number = identifier.getFoundDigits();


		nodeAnswer.writeValueScalar(number[0].value);
		auto value = nodeAnswer.readDataValue().getValue().getScalarCopy<std::string>();
		std::cout << "The following digit has been received: [" << value << "]!\n";

		photocounter++;

		std::cin.get();
	}
	
	camera.CloseFramegrabber();
}