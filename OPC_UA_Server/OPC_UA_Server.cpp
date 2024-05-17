#include "open62541pp/open62541pp.h"

#include "..//Fotoanalyses_Application/OPC_UA_Settings.h"

using namespace opcua;

int main() {
	Server server(PORT_OPC_UA_SERVER);

	// Add a programnumber node to the Objects node
	Node parentNode = server.getObjectsNode();
	Node myIntegerNode = parentNode.addVariable(
		{ PROGRAMNUMBER_NODE_NAMESPACEID, PROGRAMNUMBER_NODE_ID },
		PROGRAMNUMBER_NODE_NAME,
		VariableAttributes{}.setAccessLevel(AccessLevel::CurrentRead | AccessLevel::CurrentWrite));

	// Write node attributes
	myIntegerNode
		.writeDisplayName({ PROGRAMNUMBER_NODE_LANGUAGE, PROGRAMNUMBER_NODE_DISPLAYNAME })
		.writeDescription({ PROGRAMNUMBER_NODE_LANGUAGE, PROGRAMNUMBER_NODE_DESCRIPTION })
		.writeDataType(DataTypeId::String)
		.writeValueScalar(PROGRAMNUMBER_NODE_BASEVALUE);

	server.run();
}