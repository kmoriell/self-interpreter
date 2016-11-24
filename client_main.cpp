#include <iostream>
#include <fstream>
#include "client_proxyServer.h"
#include <unistd.h>

#define CLIENT_PARAMS 4
#define RET_OK 0
#define RET_NOK 1

#define SOLOGUI

#ifdef SOLOGUI
#include "client_mainWindow.h"
#endif

int main(int argc, char **argv) {

	#ifdef SOLOGUI

	if (argc != 3) {
		std::cout << "Argumentos: >>> .\\client <serverIP> <puerto>."
				<< std::endl;
		return RET_NOK;
	}

	std::string server = argv[1];
	std::string _port = argv[2];
	uint32_t port = stoi(_port);

	Morph morph;
	Socket socket(server, port);
	ProxyServer proxyServer(socket, morph);

	//Aca se abrio un hilo nuevo que es del proxy
	proxyServer.start();
	std::string message = LOBBY + PUNTO;
	proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
	auto app = Gtk::Application::create();
	MainWindow window(morph, proxyServer);
	app->run(*window.getWindow());

	proxyServer.interrupt();
	proxyServer.join();

	#endif

	return RET_OK;
}
