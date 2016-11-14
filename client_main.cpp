#include <iostream>
#include <fstream>
#include "client_mainWindow.h"
#include "client_proxyServer.h"
#include "common_define.h"

int main (int argc, char **argv)
{
 	if (argc != 4) {
		std::cout << "Argumentos: >>> .\\client <serverIP> <puerto> <archivo>." << std::endl;
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
	ProxyServer proxyServer(server, port, morph);

	//Aca se abrio un hilo nuevo que es del proxy
	proxyServer.start();
	std::cout << "Se abre un hilo para el proxyServer." << std::endl;

	//proxyServer.run();

	sleep(2);
	std::cout << "Seteamos el flag." << std::endl;
        std::string message = LOBBY + PUNTO;
	proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
   	auto app = Gtk::Application::create();
    	MainWindow window(morph, proxyServer);
    	app->run(*window.getWindow());

    	sleep(2);
	proxyServer.interrupt();
	proxyServer.join();
	std::cout << "JOIN." << std::endl;
	std::cout << "SALIMOS." << std::endl;
	return 0;
}
