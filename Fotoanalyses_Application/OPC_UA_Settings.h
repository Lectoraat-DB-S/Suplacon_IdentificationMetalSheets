#ifndef OPC_UA_SETTINGS_H
#define OPC_UA_SETTINGS_H

//The following macros are used to configure the OPC UA part of the application.
//--> OPC UA Server: /
#define URL_OPC_UA_SERVER "opc.tcp://LAPTOP-TCB5V9RI:4840"
#define PORT_OPC_UA_SERVER 4840

//--> Objects node: /
#define OBJECTS_NODE_NAME "Objects"
#define OBJECTS_NODE_NAMESPACEID 0

//--> Programnumber node: This node contains a programnumber found by the application
#define PROGRAMNUMBER_NODE_NAME "FoundProgramnumber"
#define PROGRAMNUMBER_NODE_DISPLAYNAME "Found Programnumber"
#define PROGRAMNUMBER_NODE_DESCRIPTION "The most recently found engraved number on a metal plate."
#define PROGRAMNUMBER_NODE_LANGUAGE "en-US"
#define PROGRAMNUMBER_NODE_BASEVALUE "0123456789"
#define PROGRAMNUMBER_NODE_NAMESPACEID 1
#define PROGRAMNUMBER_NODE_ID 1000

#endif