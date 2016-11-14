#include <iostream>
#include <fstream>
#include "client_proxyServer.h"
#include "client_morph.h"
#include <unistd.h>

int main(int argc, char **argv) {

	if (argc != 4) {
		std::cout << "Argumentos: >>> .\\client <serverIP> <puerto> <archivo>." << std::endl;
		return 1;
	}

	std::string server = argv[1];
	std::string _port = argv[2];
	uint32_t port = stoi(_port);
	std::ifstream filein(argv[3]);

	std::string message, x;

	while (filein >> x)
		message += x + " ";

	Morph morph;
	ProxyServer proxyServer(server, port, morph);

	//Aca se abrio un hilo nuevo que es del proxy
	proxyServer.start();
	std::cout << "Se abre un hilo para el proxyServer." << std::endl;

	sleep(2);
	//std::cout << "Seteamos el flag." << std::endl;
	proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
	sleep(2);
	message = "lobbyRealoded";
	proxyServer.sendCmdMessage(SET_OBJ_NAME, message);
	sleep(2);
	message = "'soy el codeSegment de lobby'.";
	proxyServer.sendCmdMessage(SET_CODESEGMENT, message);
	sleep(2);
	message = "nilSlot";
	proxyServer.sendCmdMessage(ADD_SLOT_NIL, message);
	sleep(2);
	message = "booleanSlot";
	proxyServer.sendCmdMessage(ADD_SLOT_BOOL, message);
	sleep(2);
	message = "numberSlot";
	proxyServer.sendCmdMessage(ADD_SLOT_NUMBER, message);
	sleep(2);
	message = "stringSlot";
	proxyServer.sendCmdMessage(ADD_SLOT_STRING, message);
	sleep(2);
	message = "objSlot";
	proxyServer.sendCmdMessage(ADD_SLOT_OBJECT, message);
	sleep(2);
	proxyServer.interrupt();
	proxyServer.join();
	std::cout << "JOIN." << std::endl;
	std::cout << "MUESTRO MORPH: ." << std::endl;
	morph.mostrar();
	std::cout << "SALIMOS." << std::endl;
	return 0;
}
