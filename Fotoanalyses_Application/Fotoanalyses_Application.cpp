#define PHOTOSROOT "Fotos_Plaatcodes"
#define MAX_PHOTOCOUNT 7
#define AQUISITION_DELAY
#define OCR_FONT_NAME "Industrial_0-9_NoRej"

#define URL_OPCUA_SERVER "opc.tcp://DESKTOP-SISA661:4840"

#include <iostream>

#include "HalconCpp.h"

#include "ImagePrepper.h"
#include "DigitFinder.h"
#include "DigitIdentifier.h"

using namespace std;
using namespace HalconCpp;

/*int main()
{
	HFramegrabber camera = HFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", PHOTOSROOT, "default", 1, -1);
	camera.GrabImageStart(-1);

	ImagePrepper prepper = ImagePrepper();
	DigitFinder finder = DigitFinder();
	DigitIdentifier identifier = DigitIdentifier(OCR_FONT_NAME);

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
		Digit* number = identifier.getFoundDigits();
		
		//Do something with 'number'

		photocounter++;
	}
	
	camera.CloseFramegrabber();

}*/

#include <iostream>

#include "open62541pp/open62541pp.h"

int main() {
	opcua::Client client;
	//client.connect("opc.tcp://localhost:4840");
	client.connect("opc.tcp://DESKTOP-SISA661:4840");

	opcua::Node node = client.getNode(opcua::VariableId::Server_ServerStatus_CurrentTime);
	const auto dt = node.readValueScalar<opcua::DateTime>();

	std::cout << "Server date (UTC): " << dt.format("%Y-%m-%d %H:%M:%S") << std::endl;
}
