#include <iostream>
#include "parser.h"

int main() {
	Parser parser;
	std::string cad;

	std::cout << "Testeando unaryMessage con printObj." << std::endl;
	parser.run(std::string("3 printObj."));
	parser.run(std::string("'hola' printObj."));
	parser.run(std::string("'nil' printObj."));
	std::cout << std::endl;

	std::cout << "Testeando script con multiples expresiones." << std::endl;
	parser.run(std::string("1 printObj. 'hola' print. 5."));
	std::cout << std::endl;

	std::cout << "Testeando print de numeros." << std::endl;
	//fallan todos los test de print de numero
	parser.run(std::string("3 print. 3 printObj."));
	parser.run(std::string("+2 print. +2 printObj."));
	parser.run(std::string("-1 print. -1 printObj."));
	parser.run(std::string("-1.67 print. -1.67 printObj.")); //Toma el -1. como una expresion unica no captura floats.
	parser.run(std::string("(1+1) print. (1+1) printObj.")); //No guarda bien en el code segment, le falta el .
	std::cout << std::endl;

	std::cout << "Testeando strings." << std::endl;
	parser.run(std::string("'hola' print. 'hola' printObj."));
	parser.run(std::string("'hola' print. 'hola que tal' printObj."));
	parser.run(std::string("'hola que \"'\" tal' print. 'hola que \"'\" tal' printObj.")); //falla con comillas dobles
	std::cout << std::endl;

	std::cout << "Testeando binaryMessage." << std::endl;
	parser.run(std::string("(((3*4)/2)+1) print. (((3*4)/2)+1) printObj."));
	std::cout << std::endl;

	std::cout << "Testeando espacios y caracteres ocultos." << std::endl;
	parser.run(std::string(" (\t (5*2) +1) print  . (\t (5*2) +1) printObj  . "));
	std::cout << std::endl;

	/*cad = "'hola mundo' print. ('hola-mundo') print.";

	parser.run(cad);

	cad = "2 print.  ( 1022 ) print. +16 print. -2 print.";
	parser.run(cad);

	cad = "'hola' printObj.";
	parser.run(cad);

	cad = "(2+1).";
	parser.run(cad);

	cad = "(10+1) print.";
	parser.run(cad);

	cad = "( (( 10    +1)*5) - 2 ) print . ";
	parser.run(cad);*/

	//script
	//expression
	//unary
	//receiver
	//

	return 0;
}
