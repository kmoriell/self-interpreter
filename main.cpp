#include <iostream>
#include "parser.h"

int main() {
	Parser parser;

	try {
		//Testeando print de numeros
		parser.run("    (   0   )    print    .    ")->mostrar();
		parser.run("+1 print.")->mostrar();
		parser.run("-5 print.")->mostrar();
		parser.run("102120.11230 print.")->mostrar();
		parser.run("-0.001230 print.")->mostrar();

		//Testeando print de cadenas
		parser.run("'hola' print.")->mostrar();
		parser.run("'hola-mundo' print.")->mostrar();

		parser.run("(2) print.")->mostrar();
		parser.run("('hola') print.")->mostrar();
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
