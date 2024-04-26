#define PHOTOSROOT "Fotos_Plaatcodes"
#define MAX_PHOTOCOUNT 7
#define OCR_FONT_NAME "Industrial_0-9_NoRej"

#define URL_OPCUA_SERVER "opc.tcp://DESKTOP-SISA661:4840"//"opc.tcp://LAPTOP-TCB5V9RI:4840"
#define THEANSWER_NODEID 1000

#include <iomanip>
#include <iostream>
#include <string_view>
#include <chrono>
#include <thread>

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
	std::cout << nodeAnswer.readDisplayName().getText() << "\n";
	std::cout << nodeAnswer.getNodeId().toString() << "\n";

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
		std::cout << "The answer is: [" << value << "]!\n";

		photocounter++;

		std::cin.get();
	}
	
	camera.CloseFramegrabber();

}

/// Get name of node class.
constexpr std::string_view getEnumName(opcua::NodeClass nodeClass) {
    switch (nodeClass) {
    case opcua::NodeClass::Object:
        return "Object";
    case opcua::NodeClass::Variable:
        return "Variable";
    case opcua::NodeClass::Method:
        return "Method";
    case opcua::NodeClass::ObjectType:
        return "ObjectType";
    case opcua::NodeClass::VariableType:
        return "VariableType";
    case opcua::NodeClass::ReferenceType:
        return "ReferenceType";
    case opcua::NodeClass::DataType:
        return "DataType";
    case opcua::NodeClass::View:
        return "View";
    default:
        return "Unknown";
    }
}

// Separate definition for recursion
void printNodeTree(opcua::Node<opcua::Client>& node, int indent);

// Browse and print the server's node tree recursively:
// - Objects (Object)
//   - Server (Object)
//     - Auditing (Variable)
//     - ServiceLevel (Variable)
//     - NamespaceArray (Variable)
//     - ServerArray (Variable)
//     - ServerRedundancy (Object)
//       - RedundancySupport (Variable)
//     - VendorServerInfo (Object)
// ...
void printNodeTree(opcua::Node<opcua::Client>& node, int indent) {  // NOLINT
    char buffer[10];
    int counter = 0;

    for (auto&& child : node.browseChildren()) {

        for (int i = 0; i < indent; i++)
        {
            std::cout << "->";
        }

        std::cout << itoa(counter, buffer, 10) << ". [" << child.readBrowseName().getName() 
            << "] (" << getEnumName(child.readNodeClass()) << ")\n";

        printNodeTree(child, indent + 1);

        counter++;
    }
}

/*int main() {
    opcua::Client client;
    client.connect(URL_OPCUA_SERVER);

    auto nodeRoot = client.getRootNode();
    std::cout << nodeRoot.readDisplayName().getText() << "\n";

    // Browse all nodes recursively and print node tree to console
    printNodeTree(nodeRoot, 0);

    // Browse a child node by its relative path using browse names
    auto nodeServer = nodeRoot.browseChild({ {0, "Objects"}, {0, "Server"} });
    // Browse the parent node
    auto nodeServerParent = nodeServer.browseParent();

    std::cout << nodeServer.readDisplayName().getText() << "'s parent node is "
        << nodeServerParent.readDisplayName().getText() << "\n";
    std::cout << nodeServer.getNodeId().toString() << "\n";
    
    //Find the answer!
    auto nodeAnswer = nodeRoot.browseChild({ {0, "Objects"}, {1, "TheAnswer"} });
    std::cout << nodeAnswer.readDisplayName().getText() << "\n";
    std::cout << nodeAnswer.getNodeId().toString() << "\n";
    nodeAnswer.writeValueScalar(1);
    auto value = nodeAnswer.readDataValue().getValue().getScalarCopy<INT32>();
    std::cout << "The answer is: [" << value << "]!\n";
}*/

/*int main() {
    opcua::Client client;

    // Add a state callback (session activated) to create subscription(s) and monitored items(s) in
    // a newly activated session. If the client is disconnected, the subscriptions and monitored
    // items are deleted. This approach with the state callback assures, that the subscriptions are
    // recreated whenever the client reconnects to the server.
    client.onSessionActivated([&] {
        auto sub = client.createSubscription();

        // Modify and delete the subscription via the returned Subscription<T> object
        opcua::SubscriptionParameters subscriptionParameters{};
        subscriptionParameters.publishingInterval = 1000.0;
        sub.setSubscriptionParameters(subscriptionParameters);
        sub.setPublishingMode(true);
        // sub.deleteSubscription();

        // Create a monitored item within the subscription for data change notifications
        auto nodeAnswer = opcua::NodeId(1, THEANSWER_NODEID);
        auto mon = sub.subscribeDataChange(
            nodeAnswer,  // monitored node id
            opcua::AttributeId::Value,  // monitored attribute
            [&](uint32_t subId, uint32_t monId, const opcua::DataValue& value) {
                const opcua::MonitoredItem item(client, subId, monId);
                std::cout
                    << "Data change notification:\n"
                    << "- subscription id:   " << item.subscriptionId() << "\n"
                    << "- monitored item id: " << item.monitoredItemId() << "\n"
                    << "- node id:           " << item.getNodeId().toString() << "\n"
                    << "- attribute id:      " << static_cast<int>(item.getAttributeId()) << "\n";

                char buffer[10];
                const auto dt = value.getValue().getScalarCopy<INT32>();
                //std::cout << "Current server time (UTC): " << dt.format("%H:%M:%S") << std::endl;
                std::cout << itoa(dt, buffer, 10) << std::endl;
            }
        );

        // Modify and delete the monitored item via the returned MonitoredItem<T> object
        opcua::MonitoringParametersEx monitoringParameters{};
        monitoringParameters.samplingInterval = 100.0;
        mon.setMonitoringParameters(monitoringParameters);
        mon.setMonitoringMode(opcua::MonitoringMode::Reporting);
        // mon.deleteMonitoredItem();
        });

    // Endless loop to automatically (try to) reconnect to server.
    while (true) {
        try {
            client.connect(URL_OPCUA_SERVER);
            // Run the client's main loop to process callbacks and events.
            // This will block until client.stop() is called or an exception is thrown.
            client.run();
        }
        catch (const opcua::BadStatus& e) {
            // Workaround to enforce a new session
            // https://github.com/open62541pp/open62541pp/issues/51
            client.disconnect();
            std::cout << "Error: " << e.what() << "\nRetry to connect in 3 seconds\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}*/
