#include "server_proxyClient.h"

ProxyClient::ProxyClient(Socket &socket, Server &server, Workspace* workspace) : Proxy(socket), server(server) {
	this->workspace = workspace;
}

void ProxyClient::execLobbyCMD(std::string &cad) {
	objClientView = server.receiveCode(cad);
	ParserProtocoloServidor parser(objClientView);
	sendOK(parser.getString());
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
			case EXEC_LOBBY_CMD:
				cad = clientMessage.getMessage();
				execLobbyCMD(cad);
				break;
			case SHOW_LOBBY:
				break;
			case EXEC_LOCAL_CMD:
				break;
			case SET_OBJ_NAME:
				cad = clientMessage.getMessage();
				setObjName(cad);
				break;
			case SET_SLOT_NAME:
				break;
			case ADD_SLOT_NIL:
				break;
			case ADD_SLOT_BOOL:
				break;
			case ADD_SLOT_NUMBER:
				break;
			case ADD_SLOT_STRING:
				break;
			case ADD_SLOT_OBJECT:
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
