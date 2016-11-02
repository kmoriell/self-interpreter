#include <iostream>
#include <fstream>
#include "parser.h"

int main(int argc, char **argv) {

	if (argc != 2) {
		std::cout << "Falta el archivo a procesar." << std::endl;
		return 1;
	}

	std::ifstream filein(argv[1]);

	std::string script, x;

	while (filein >> x)
		script += x + " ";

	Parser parser(script);
	std::string cad;
	Object *lobby = new Object();
	lobby->addSlot("lobby", lobby, true, false, false);
	parser.setContext(lobby);

	/*std::cout << "Testeando unaryMessage con printObj." << std::endl;
	cad = "3 printObj.";
	parser.run(cad);
	cad = "'hola' printObj.";
	parser.run(cad);
	cad = "'hola' printObj.";
	parser.run(cad);
	std::cout << std::endl;

	std::cout << "Testeando script con multiples expresiones." << std::endl;
	cad = "1 printObj. 'hola' print. 5.";
	parser.run(cad);
	std::cout << std::endl;

	std::cout << "Testeando booleans." << std::endl;
	cad = "true print. true printObj.";
	parser.run(cad);
	cad = "false print. false printObj.";
	parser.run(cad);
	std::cout << std::endl;

	std::cout << "Testeando print de numeros." << std::endl;
	//fallan todos los test de print de numero
	cad = "3 print. 3 printObj.";
	parser.run(cad);
	cad = "+2 print. +2 printObj.";
	parser.run(cad);
	cad = "-1 print. -1 printObj.";
	parser.run(cad);
	cad = "-1.67 print. -1.67 printObj.";
	parser.run(cad); //Toma el -1. como una expresion unica no captura floats.
	cad = "(1+1) print. (1+1) printObj.";
	parser.run(cad); //No guarda bien en el code segment, le falta el .
	std::cout << std::endl;

	std::cout << "Testeando strings." << std::endl;
	cad = "'hola' print. 'hola' printObj.";
	parser.run(cad);
	cad = "'hola' print. 'hola que tal' printObj.";
	parser.run(cad);
	cad = "'hola que \"'\" tal' print. 'hola que \"'\" tal' printObj.";
	parser.run(cad); //falla con comillas dobles
	std::cout << std::endl;

	std::cout << "Testeando binaryMessage." << std::endl;
	cad = "(((3*4)/2)+1) print. (((3*4)/2)+1) printObj.";
	parser.run(cad);
	std::cout << std::endl;

	std::cout << "Testeando espacios y caracteres ocultos." << std::endl;
	cad = " (\t (5*2) +1) print  . (\t (5*2) +1) printObj  . ";
	parser.run(cad);
	std::cout << std::endl;*/

	//std::cout << "Testeando objetos." << std::endl;
	//cad = "(lobby _AddSlots: (|punto = (||3.).|)). (punto + 1) printObj.";
	//std::cout << "filein = " << script << std::endl;
	//std::cout << "   cad = " << cad << std::endl;

	parser.run();
	/*cad = "(||) printObj.";
	parser.run(cad);*/
	//cad = "(|x=3.|) printObj.";
	//parser.run(cad);

	return 0;
}
