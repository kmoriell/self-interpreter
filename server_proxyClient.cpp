#include "server_proxyClient.h"

ProxyClient::ProxyClient(Socket &socket, Server &server, Workspace* workspace) : Proxy(socket), server(server) {
	this->workspace = workspace;
}

void ProxyClient::execLobbyCMD(std::string code) {
	objClientView = server.receiveCode(code);
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

			switch (this->clientMessage.getCommand()) {
			case EXEC_LOBBY_CMD:
				execLobbyCMD(clientMessage.getMessage());
				break;
			case SHOW_LOBBY:
				break;
			case EXEC_LOCAL_CMD:
				break;
			case SET_OBJ_NAME:
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
			default:
				sendError("Comando desconocido.");
			}
		} catch (const std::runtime_error &e) {
			if (!_interrupt)
				throw e;
		}
	}
}
