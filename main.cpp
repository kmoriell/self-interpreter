#include <iostream>
#include "parser.h"

int main() {
	Parser parser;
	std::string cad;

	//Testeando print de numeros
	cad = "'hola mundo' print. ('hola-mundo') print.";
	parser.run(cad);

	cad = "2 print.  ( 1022 ) print. +16 print. -2 print.";
	parser.run(cad);

	cad = "'hola'.";
	parser.run(cad);

	cad = "(2+1).";
	parser.run(cad);

	cad = "(10+1) print.";
	parser.run(cad);

	cad = "( (( 10    +1)*5) - 2 ) print . ";
	parser.run(cad);

	//script
	//expression
	//unary
	//receiver
	//

	/*cad = "    (   0   )    print    .    ";
	parser.run(cad);
	cad = "+1 print.";
	parser.run(cad);
	cad = "-5 print.";
	parser.run(cad);
	cad = "102120.11230 print.";
	parser.run(cad);
	cad = "-0.001230 print.";
	parser.run(cad);

	//Testeando print de cadenas
	cad = "'hola' print.";
	parser.run(cad);
	cad = "'hola-mundo' print.";
	parser.run(cad);
	cad = "(2) print.";
	parser.run(cad);
	cad = "('hola') print.";
	parser.run(cad);*/

	return 0;
}
