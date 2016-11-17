#include <iostream>
#include <fstream>
#include "client_proxyServer.h"
#include "common_define.h"

// #define SOLOGUI

#ifdef SOLOGUI
#include "client_mainWindow.h"
#endif


int main(int argc, char **argv) {
	if (argc != 4) {
		std::cout << "Argumentos: >>> .\\client <serverIP> <puerto> <archivo>."
				<< std::endl;
		return 1;
	}

	std::string server = argv[1];
	std::string _port = argv[2];
	uint32_t port = stoi(_port);
	std::ifstream filein(argv[3]);

	std::string script, x;

	while (filein >> x)
		script += x + " ";

	Morph morph;
	Socket socket(server, port);
	ProxyServer proxyServer(socket, morph);

	//Aca se abrio un hilo nuevo que es del proxy
	proxyServer.start();
	std::cout << "Se abre un hilo para el proxyServer." << std::endl;

	std::cout << "Seteamos el flag." << std::endl;

	#ifdef SOLOGUI
	std::string message = LOBBY + PUNTO;
	proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
	auto app = Gtk::Application::create();
	MainWindow window(morph, proxyServer);
	app->run(*window.getWindow());
	#else
	std::string message = script;
	proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
    #endif
	proxyServer.interrupt();
	proxyServer.join();
	std::cout << "JOIN." << std::endl;
	std::cout << "SALIMOS." << std::endl;
	return 0;
}
