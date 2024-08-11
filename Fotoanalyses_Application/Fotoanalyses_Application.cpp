#include "Fotoanalyses_Settings.h"

using namespace HalconCpp;
using namespace opcua;

int main()
{
	HFramegrabber camera;
	ImagePrepper prepper;
	DigitFinder finder;
	DigitIdentifier identifier;
	Client client;

	HImage image;
	BYTE photocounter = 0;

	ApplicationStatus currentStatus = InitializingObjects;
	bool unknownStatus = false;

	while (!unknownStatus)
	{
		switch (currentStatus)
		{
		case InitializingObjects:
		{
			camera = HFramegrabber(INTERFACE_NAME, RESOLUTION, RESOLUTION, 0, 0, 0, 0, FIELD, -1, "default", -1, "false", PHOTOSROOT, DEVICE_NAME, PORT, -1);
			identifier = DigitIdentifier(OCR_FONT_NAME);

			currentStatus = ConnectingToServer;
		}
		break;
		case ConnectingToServer:
		{
			try {
				client.connect(URL_OPC_UA_SERVER);

				Node<Client> nodeProgramnumber = client.getRootNode().browseChild({
				{OBJECTS_NODE_NAMESPACEID, OBJECTS_NODE_NAME},
				{PROGRAMNUMBER_NODE_NAMESPACEID, PROGRAMNUMBER_NODE_NAME} });
				std::cout << "---Information about the \"" << nodeProgramnumber.readDisplayName().getText() << "\" node---\n";
				std::cout << "Description: \"" << nodeProgramnumber.readDescription().getText() << "\"\n";
				std::cout << "ID: (" << nodeProgramnumber.id().toString() << ")\n";
				std::cout << "Value: [" << nodeProgramnumber.readDataValue().getValue().getScalarCopy<std::string>() << "]\n";
				std::cout << "---End Information---\n";

				currentStatus = StartingImageAquisition;
			}
			catch (const opcua::BadStatus& e) {
				client.disconnect();
				std::cout << "Error: " << e.what() << "\nRetry to connect in 3 seconds\n";
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		break;
		case WritingToNode:
		{
			Node<Client> nodeProgramnumber = client.getRootNode().browseChild({
				{OBJECTS_NODE_NAMESPACEID, OBJECTS_NODE_NAME},
				{PROGRAMNUMBER_NODE_NAMESPACEID, PROGRAMNUMBER_NODE_NAME} });
			std::string foundProgramnumber = identifier.GetFoundNumber();

			nodeProgramnumber.writeValueScalar(foundProgramnumber);
			std::string value = nodeProgramnumber.readDataValue().getValue().getScalarCopy<std::string>();
			std::cout << "The programnumber [" << value << "] has been send to & received by the server!\n";

			currentStatus = WaitingForInput;
		}
		break;
		case StartingImageAquisition:
		{
			std::cout << "Starting image acquisition...\n";
			camera.GrabImageStart(-1);
			currentStatus = AquiringImage;
		}
		break;
		case AquiringImage:
		{
			photocounter++;

			if (photocounter <= MAX_PHOTOCOUNT)
			{
				image = camera.GrabImageAsync(MAX_DELAY);
#if !IS_GRAYSCALE
				image = image.Rgb1ToGray();
#endif

				std::cout << "New image acquired!\n";
				currentStatus = PreppingImage;
#if SAVING_PHOTOS
				image.WriteImage("png", 255, std::to_string((int)photocounter).c_str());
#endif
			}
			else
				currentStatus = EndingImageAquisition;
		}
		break;
		case EndingImageAquisition:
		{
			camera.CloseFramegrabber();
			std::cout << "Ending image acquisition...\n";
			currentStatus = None;
		}
		break;
		case PreppingImage:
		{
			prepper.execute(image);
			prepper.print();
			currentStatus = FindingDigits;
		}
		break;
		case FindingDigits:
		{
			finder.execute(prepper.getImage());
			finder.print();
			currentStatus = IdentifyingDigits;
		}
		break;
		case IdentifyingDigits:
		{
			identifier.execute(prepper.getImage(), finder.getOutlineDigits());
			identifier.print();
			currentStatus = WritingToNode;
		}
		break;
		case WaitingForInput:
		{
			std::cout << "Press ENTER to take a new photo...";

			char input = '0';
			while (input != '\n')
				input = std::cin.get();

			currentStatus = AquiringImage;
		}
		break;
		default:
		{
			unknownStatus = true;
			std::cout << "Shutting down Fotoanalyses Application...\n";
		}
		break;
		}
	}
}