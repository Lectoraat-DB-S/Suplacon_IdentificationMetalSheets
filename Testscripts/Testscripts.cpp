#define TESTPHOTOS_ROOT "../Testfotos_Plaatcodes/Original"
#define MAX_PHOTOCOUNT 2
#define OCR_FONT_NAME "Industrial_0-9_NoRej"

//Constants used for configuring the testscripts
#define NUMBERS_ON_TESTPHOTOS {"1963814007", "1963814005"} 

#define STORAGE_RESULTPHOTOS_ROOT "../Testfotos_Plaatcodes"
#define LOCATION_PERFORMANCE_RESULTPHOTOS "/Performance"

#define RUN_PERFORMANCE_TESTS true
#define RUN_FUNCTIONAL_TESTS false
#define RUN_UNITTESTS false
//--- --- ---

#include <iomanip>
#include <iostream>

#include "HalconCpp.h"
#include "open62541pp/open62541pp.h"

#include "../Fotoanalyses_Application/ImagePrepper.h"
#include "../Fotoanalyses_Application/DigitFinder.h"
#include "../Fotoanalyses_Application/DigitIdentifier.h"
#include "../Fotoanalyses_Application/OPC_UA_Settings.h"

using namespace HalconCpp;
using namespace opcua;

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
	WaitingForInput,

	//Extra statuses for testing purposes
	SavingTestresult,
	ShowingTestresults,
	ExportingTestresults,
	FinishedTesting
	//--- --- ---
};

void executePerformanceTests()
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

	//Addition Performance Testing
	std::string expectedNumbers[] = NUMBERS_ON_TESTPHOTOS;
	std::string foundNumbers[MAX_PHOTOCOUNT];
	//--- --- ---

	while (!unknownStatus)
	{
		//Addition Performance Testing
		if (currentStatus == WaitingForInput)
			currentStatus = SavingTestresult;
		else if(currentStatus == None)
			currentStatus = ShowingTestresults;
		//--- --- ---

		switch (currentStatus)
		{

		//Addition Performance Testing
		case SavingTestresult:
		{
			std::cout << "Saving testresult...\n";
			foundNumbers[photocounter - 1] = identifier.GetFoundNumber();
			currentStatus = AquiringImage;
		}
		break;
		case ShowingTestresults:
		{
			std::cout << "---Results Performance Test---\n";
			for (UINT16 i = 1; i <= MAX_PHOTOCOUNT; i++)
			{
				std::cout << "Photo ID: " << i
					<< ", Expected: " << expectedNumbers[i - 1]
					<< ", Found: " << foundNumbers[i - 1]
					<< ", Is Match? " << ((expectedNumbers[i - 1] == foundNumbers[i - 1]) ? "YES" : "NO")
					<< "\n";
			}
			std::cout << "---End Performance Test---\n";
			currentStatus = ExportingTestresults;
		}
		break;
		case ExportingTestresults:
		{
			currentStatus = FinishedTesting;
		}
		break;
		//--- --- ---

		case InitializingObjects:
		{
			camera = HFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", TESTPHOTOS_ROOT, "default", 1, -1);
			identifier = DigitIdentifier(OCR_FONT_NAME);

			currentStatus = ConnectingToServer;
		}
		break;
		case ConnectingToServer:
		{
			try {
				client.connect(URL_OPC_UA_SERVER);

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
				image = camera.GrabImageAsync(-1);
				std::cout << "New image acquired!\n";
				currentStatus = PreppingImage;
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

int main()
{
	if (RUN_PERFORMANCE_TESTS)
	{
		executePerformanceTests();
	}
}

