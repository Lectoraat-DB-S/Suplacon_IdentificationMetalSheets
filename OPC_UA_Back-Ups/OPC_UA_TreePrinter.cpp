#define URL_OPCUA_SERVER "opc.tcp://LAPTOP-TCB5V9RI:4840" //"opc.tcp://DESKTOP-SISA661:4840"
#define THEANSWER_NODEID 1000

#include <iomanip>
#include <iostream>
#include <string_view>
#include <chrono>
#include <thread>

#include "open62541pp/open62541pp.h"

using namespace std;


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

int main() {
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
}