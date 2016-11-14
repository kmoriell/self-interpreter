#include <iostream>
#include <fstream>

#include "server_accepter.h"
#include "server_server.h"
#include "common_define.h"

void exit_routine(Accepter* connections_accepter) {
	// mando la señal para interrumpir el aceptador de conexiones
	connections_accepter->interrupt();
	connections_accepter->join();
}

int main(int argc, char **argv) {
	//Bipaseamos el server-client para testear el parser localmente
	/*std::string cad;
	if (argc != 2) {
		std::cerr << "Forma de uso: >>> ./server <numeroPuerto>" << std::endl;
		return 1;
	}

	try {
		int port = std::stoi(argv[1]);

		Server server;

		Accepter *connections_accepter = new Accepter(port, server);
		// Este hilo va a estar corriendo durante toda la ejecucion del programa
		connections_accepter->start();

		char c = '\0';
		while (c != 'q') {
			std::cin.get(c);
		}
		exit_routine(connections_accepter);
		delete connections_accepter;
	} catch (const std::runtime_error &e) {
		std::cout << "Error. " << std::endl << e.what() << std::endl;
	} catch (...) {
		std::cout << "Error desconocido." << std::endl << std::endl;
	}*/

	// >>> .\tp server pruebas/*.self
	if (argc != 2) {
	 std::cout << "Falta el archivo a procesar." << std::endl;
	 return 1;
	 }

	 std::ifstream filein(argv[1]);
	 std::string script, x;
	 while (filein >> x)
	 script += x + " ";

	 //std::cout << "SCRIPT A EJECUTAR: " << std::endl << script << std::endl;
	 std::string cad;
	 Object *lobby = new Object();
	 lobby->setName(LOBBY);
	 std::cout << "Lobby context: " << lobby << std::endl;
	 lobby->addSlot(LOBBY, lobby, false, false, false);

	 VirtualMachine vm;
	 Parser parser(vm);
	 parser.setContext(lobby);

	 Object* obj;
	 std::vector<Object*> _vector = parser.run(script);
	 ;
	 obj = _vector[_vector.size() - 1];
	 std::cout << std::endl << "Objeto Salida para dibujar: " << std::endl;
	 obj->printObj(std::vector<Object*> { });

	/*std::cout << std::endl << "Dibujando.. " << std::endl;
	 Morph unMorph;
	 std::string cadMorph = ParserProtocoloServidor(obj).getString();
	 ParserProtocoloCliente(unMorph, cadMorph);
	 delete lobby;
	 return 0;*/

	return 0;
}
