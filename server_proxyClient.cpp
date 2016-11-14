#include "server_proxyClient.h"

void ProxyClient::execLobbyCMD(std::string code) {
	Object* obj = server.receiveCode(code);
	ParserProtocoloServidor parser(obj);
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
			case -1:
				// TODO: error
				break;
			case EXEC_LOBBY_CMD:
				execLobbyCMD(clientMessage.getMessage());
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
