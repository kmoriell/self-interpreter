#include "client_proxyServer.h"

ProxyServer::ProxyServer(Socket &socket, Morph &morph, std::vector<std::string> &workspaces) :
		Proxy(socket), morph(morph), workspaces(workspaces) {
	this->serverSocket.connect();
	this->flag = false;
	//this->command = ERRORMESSAGE;
	//this->message = "";
}

bool ProxyServer::sendCmdMessage(char command, std::string &message) {
	if (flag)
		return false;
	else {
		morph.clear();
		std::cout << "comando a enviar: " << command << std::endl;
		std::cout << "mensaje a enviar: " << message << std::endl;
		clientMessage.setCommand(command);
		clientMessage.setMessage(message.c_str());
		clientMessage.setLength(message.size());
		this->flag = true;
		return true;
	}
}

void ProxyServer::sendCMDMessage() {
	this->send(clientMessage);
}

void ProxyServer::run() {
	while (!_interrupt) {
		if (flag) {
			try {
				//Envio el mensaje al servidor
				sendCMDMessage();
				//Recibo el resultado del mensaje enviado
				int s = receive();
				if (s == 0) {
					finished = true;
					break;
				}

				std::string mensajeRecibido;

				switch (clientMessage.getCommand()) {
				case ERRORMESSAGE: {
					std::cout << "El servidor devolvio error." << std::endl;
					errorMsg = clientMessage.getMessage();
					break;
				}
				case OK_MSG_MORPH: {
					std::cout << "Se recibio un mensaje OK" << std::endl;
					mensajeRecibido = clientMessage.getMessage();
					ParserProtocoloMorph parser(morph, mensajeRecibido);
					break;
				}
				case OK_MSG_SELECT_WKS: {
					std::cout << "Se recibio un mensaje OK de WKS" << std::endl;
					mensajeRecibido = clientMessage.getMessage();
					ParserProtocoloWorkspaces parser(workspaces, mensajeRecibido);
					break;
				}
				default:
					std::cout << "no se que mandaste" << std::endl;
					break;
				}

			} catch (const std::runtime_error &e) {
				if (!_interrupt)
					throw e;
			}
			flag = false;
		}
	}
}
bool ProxyServer::getFlag() const {
	return flag;
}
bool ProxyServer::areThereErrors() const {
	return (errorMsg.size() > 0);
}
std::string ProxyServer::getErrors() {
	std::string copy = errorMsg;
	errorMsg.clear();
	return copy;
}

