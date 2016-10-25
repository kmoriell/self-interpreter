#include <iostream>
#include "parser.h"

int main() {
	Parser parser;
	/*if (parser.esString("'hola'"))
		std::cout << "Verdadero" << std::endl;
	else
		std::cout << "Falso" << std::endl;*/

	Object *msg;

	//Testeando print de numeros
	parser.script("0 print.")->mostrar();
	parser.script("+1 print.")->mostrar();
	parser.script("-5 print.")->mostrar();
	parser.script("102120.11230 print.")->mostrar();
	parser.script("-0.001230 print.")->mostrar();

	//Testeando print de cadenas
	parser.script("'hola' print.")->mostrar();
	parser.script("'hola-mundo' print.")->mostrar();

	//parser.script("'nil'.")->mostrar();
	return 0;
}
