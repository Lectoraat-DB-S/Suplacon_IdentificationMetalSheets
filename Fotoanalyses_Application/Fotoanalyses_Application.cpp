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

#include "OPC_UA_Settings.h"

using namespace HalconCpp;
using namespace opcua;

int main()
{
	HFramegrabber camera = HFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", PHOTOSROOT, "default", 1, -1);
	ImagePrepper prepper = ImagePrepper();
	DigitFinder finder = DigitFinder();
	DigitIdentifier identifier = DigitIdentifier(OCR_FONT_NAME);

	Client client;
	client.connect(URL_OPC_UA_SERVER);

	auto nodeProgramnumber = client.getRootNode().browseChild({ {OBJECTS_NODE_NAMESPACEID, OBJECTS_NODE_NAME}, {PROGRAMNUMBER_NODE_NAMESPACEID, PROGRAMNUMBER_NODE_NAME} });
	std::cout << "---Information about the \"" << nodeProgramnumber.readDisplayName().getText() << "\" node---\n";
	std::cout << "Description: \"" << nodeProgramnumber.readDescription().getText() << "\"\n";
	std::cout << "ID: (" << nodeProgramnumber.getNodeId().toString() << ")\n";
	std::cout << "Value: [" << nodeProgramnumber.readDataValue().getValue().getScalarCopy<std::string>() << "]\n";
	std::cout << "---End Information---\n";

	std::cout << "---Start image acquisition---\n";
	camera.GrabImageStart(-1);

	BYTE photocounter = 0;
	while (photocounter < MAX_PHOTOCOUNT)
	{
		HImage image = camera.GrabImageAsync(-1);
		std::cout << "New image acquired!\n";

		prepper.execute(image);
		prepper.print();
		HImage preppedImage = prepper.getImage();

		finder.execute(preppedImage);
		finder.print();
		HRegion outlineDigits = finder.getOutlineDigits();

		identifier.execute(preppedImage, outlineDigits);
		identifier.print();
		Digit* number = identifier.getFoundDigits();

		nodeProgramnumber.writeValueScalar(number[0].value);
		auto value = nodeProgramnumber.readDataValue().getValue().getScalarCopy<std::string>();
		std::cout << "The following digit has been received: [" << value << "]!\n";

		photocounter++;

		std::cout << "Press ENTER to continue...";
		std::cin.get();
	}
	
	camera.CloseFramegrabber();
	std::cout << "---End image acquisition---\n";
}