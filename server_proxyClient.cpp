#include "server_proxyClient.h"
#include <string>
#include <iostream>

ProxyClient::ProxyClient(Socket &socket, Server &server, Workspace* workspace) :
		Proxy(socket), server(server) {
	this->workspace = workspace;
}

void ProxyClient::execLobbyCMD(std::string &cad) {
	try {
		objClientView = server.receiveCode(cad);
		ParserProtocoloServidor parser(objClientView);
		sendOK(parser.getString());
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::setObjName(const std::string &cad) {
	objClientView->setName(cad);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
}

void ProxyClient::addSlotNil(const std::string &cad) {
	Object* _obj = workspace->getVirtualMachine()->createNil();
	objClientView->addSlot(cad, _obj, true, false, false);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
}

void ProxyClient::addSlotBoolean(const std::string &cad) {
	Object* _obj = workspace->getVirtualMachine()->createBoolean(
			BOOLEAN_OBJ_DEFAULT);
	objClientView->addSlot(cad, _obj, true, false, false);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
}

void ProxyClient::addSlotNumber(const std::string &cad) {
	Object* _obj = workspace->getVirtualMachine()->createNumber(
			NUMBER_OBJ_DEFAULT);
	objClientView->addSlot(cad, _obj, true, false, false);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
}

void ProxyClient::addSlotString(const std::string &cad) {
	std::string stringValue = STRING_OBJ_DEFAULT;
	Object* _obj = workspace->getVirtualMachine()->createString(stringValue);
	objClientView->addSlot(cad, _obj, true, false, false);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
}

void ProxyClient::addSlotObject(const std::string &cad) {
	Object* _obj = workspace->getVirtualMachine()->createEmptyObject();
	objClientView->addSlot(cad, _obj, true, false, false);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
}

void ProxyClient::setCodeSegment(const std::string &cad) {
	objClientView->setCodeSegment(cad);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
}

void ProxyClient::run() {
	while (!_interrupt) {
		try {
			int s = this->receive();
			if (s == 0) {
				finished = true;
				break;
			}

			std::string cad = "";
			switch (this->clientMessage.getCommand()) {
			case EXEC_LOBBY_CMD: {
				cad = clientMessage.getMessage();
				execLobbyCMD(cad);
				break;
			}
			case SHOW_LOBBY:
				break;
			case EXEC_LOCAL_CMD:
				break;
			case SET_OBJ_NAME: {
				cad = clientMessage.getMessage();
				setObjName(cad);
				break;
			}
			case SET_SLOT_NAME:
				break;
			case ADD_SLOT_NIL: {
				cad = clientMessage.getMessage();
				addSlotNil(cad);
				break;
			}
			case ADD_SLOT_BOOL:
				cad = clientMessage.getMessage();
				addSlotBoolean(cad);
				break;
			case ADD_SLOT_NUMBER:
				cad = clientMessage.getMessage();
				addSlotNumber(cad);
				break;
			case ADD_SLOT_STRING:
				cad = clientMessage.getMessage();
				addSlotString(cad);
				break;
			case ADD_SLOT_OBJECT:
				cad = clientMessage.getMessage();
				addSlotObject(cad);
				break;
			case REMOVE_SLOT:
				break;
			case SWAP_MUTABILITY:
				break;
			case ADD_ARGUMENT_SLOT:
				break;
			case ADD_PARENT_SLOT:
				break;
			case SET_CODESEGMENT:
				cad = clientMessage.getMessage();
				setCodeSegment(cad);
				break;
			default:
				sendError("Comando desconocido.");
			}
		} catch (const std::runtime_error &e) {
			if (!_interrupt)
				throw e;
		}
	}
}
