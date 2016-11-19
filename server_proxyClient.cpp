#include "server_proxyClient.h"
#include <string>
#include <iostream>

ProxyClient::ProxyClient(Socket &socket, Server &server) :
		Proxy(socket), server(server) {
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

void ProxyClient::execLocalCMD(std::string &cad) {
	try {
		objClientView = server.receiveCode(objClientView, cad);
		ParserProtocoloServidor parser(objClientView);
		sendOK(parser.getString());
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::showLobby() {
	try {
		objClientView = server.getLobby();
		ParserProtocoloServidor parser(objClientView);
		sendOK(parser.getString());
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::execRefresh() {
	try {
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
			case SHOW_LOBBY: {
				showLobby();
				break;
			}
			case EXEC_REFRESH: {
				execRefresh();
				break;
			}
			case EXEC_LOCAL_CMD: {
				cad = clientMessage.getMessage();
				execLocalCMD(cad);
				break;
			}
			case ADD_SLOT: {
				cad += ADD_SLOTS_METHOD + OP_ARG + P_LEFT + SLOT_LIST_SEP;
				cad += clientMessage.getMessage();
				cad += SLOT_LIST_SEP + P_RIGHT + PUNTO;
				execLocalCMD(cad);
				break;
			}
			case SET_OBJ_NAME: {
				cad = clientMessage.getMessage();
				setObjName(cad);
				break;
			}
			case SET_CODESEGMENT: {
				cad = clientMessage.getMessage();
				setCodeSegment(cad);
				break;
			}
			default:
				sendError("Comando desconocido.");
			}
		} catch (const std::runtime_error &e) {
			if (!_interrupt)
				throw e;
		}
	}
}
