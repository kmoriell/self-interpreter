#include <iostream>
#include <fstream>
#include "parser.h"
#include "morph.h"
#include "parserProtocoloCliente.h"
#include "parserProtocoloServidor.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Falta el archivo a procesar." << std::endl;
		return 1;
	}

	std::ifstream filein(argv[1]);
	std::string script, x;
	while (filein >> x)
		script += x + " ";

	//std::cout << "SCRIPT A EJECUTAR: " << std::endl << script << std::endl;
	Parser parser(script);
	std::string cad;
	Object *lobby = new Object();
	lobby->setName("lobby");
	std::cout << "Lobby context: " << lobby << std::endl;
	lobby->addSlot("lobby", lobby, false, false, false);
	parser.setContext(lobby);

	Object* obj;
	std::vector<Object*> _vector = parser.run();;
	obj = _vector[_vector.size() - 1];
	std::cout << std::endl << "Objeto Salida para dibujar: " << std::endl;
	obj->printObj(std::vector<Object*>{});

	std::cout << std::endl << "Dibujando.. " << std::endl;
	Morph unMorph;
	std::string cadMorph = ParserProtocoloServidor(obj).getString();
	ParserProtocoloCliente(unMorph, cadMorph);
	return 0;

	delete lobby;
	return 0;
}
