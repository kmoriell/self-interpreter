#include "server_proxyClient.h"
#include <string>
#include <iostream>
#include <vector>

ProxyClient::ProxyClient(Socket &socket, Server &server) :
		Proxy(socket), server(server) {
	sckptr = &socket;
}

ProxyClient::~ProxyClient() {
	delete sckptr;
}

void ProxyClient::execLobbyCMD(std::string &cad) {
	try {
		std::string sendMsg;
		uint32_t lobbyId = ID_LOBBY;
		sendMsg = server.receiveCode(idWorkspace, lobbyId, cad);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::execLocalCMD(std::string &cad) {
	try {
		std::string sendMsg;
		sendMsg = server.receiveCode(idWorkspace, idObj, cad);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::showLobby() {
	try {
		std::string sendMsg;
		sendMsg = server.getLobby(idWorkspace, idObj);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::execRefresh() {
	try {
		std::string sendMsg;
		sendMsg = server.getObj(idWorkspace, idObj);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::setObjName(const std::string &cad) {
	try {
		std::string sendMsg;
		sendMsg = server.setObjName(idWorkspace, idObj, cad);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::setCodeSegment(const std::string &cad) {
	try {
		std::string sendMsg;
		sendMsg = server.setCodeSegment(idWorkspace, idObj, cad);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::getSlotObj(const std::string &cad) {
	try {
		std::string sendMsg;
		sendMsg = server.getSlotObj(idWorkspace, idObj, cad);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::swapMutability(const std::string &cad) {
	try {
		std::string sendMsg;
		sendMsg = server.swapMutability(idWorkspace, idObj, cad);
		sendOK(sendMsg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::availableWks() {
	try {
		std::vector<std::string> vecWks = server.availableWorkspace();
		std::string msg;
		for (std::string str : vecWks) {
			msg += str + CHAR_SEPARADOR;
		}
		msg = msg.substr(0, msg.size()-1);
		sendOKWks(msg);
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::loadWks(const std::string &cad) {
	try {
		idWorkspace = cad;
		showLobby();
	} catch (const std::runtime_error &e) {
		idWorkspace.clear();
		sendError(e.what());
	} catch (...) {
		idWorkspace.clear();
		sendError("Error desconocido.");
	}
}

void ProxyClient::newWks(const std::string &cad) {
	try {
		server.newWorkspace(cad);
		availableWks();
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::deleteWks(const std::string &cad) {
	try {
		server.deleteWorkspace(cad);
		availableWks();
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
}

void ProxyClient::closeWks(const std::string &cad) {
	try {
		server.closeWorkspace(cad);
		availableWks();
		idWorkspace.clear();
	} catch (const std::runtime_error &e) {
		sendError(e.what());
	} catch (...) {
		sendError("Error desconocido.");
	}
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
			std::cout << "idObjEnVista por el cliente: " << idObj << std::endl;
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
			case REMOVE_SLOT: {
				cad += REMOVE_SLOTS_METHOD + OP_ARG + P_LEFT + SLOT_LIST_SEP;
				cad += clientMessage.getMessage();
				cad += PUNTO + SLOT_LIST_SEP + P_RIGHT + PUNTO;
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
			case GET_SLOT_OBJ: {
				cad = clientMessage.getMessage();
				getSlotObj(cad);
				break;
			}
			case SWAP_MUTABILITY: {
				cad = clientMessage.getMessage();
				swapMutability(cad);
				break;
			}
			case AVAILABLE_WKS: {
				availableWks();
				break;
			}
			case LOAD_WK: {
				cad = clientMessage.getMessage();
				loadWks(cad);
				break;
			}
			case NEW_WK: {
				cad = clientMessage.getMessage();
				newWks(cad);
				break;
			}
			case DELETE_WK: {
				cad = clientMessage.getMessage();
				deleteWks(cad);
				break;
			}
			case CLOSE_WK: {
				cad = clientMessage.getMessage();
				closeWks(cad);
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
