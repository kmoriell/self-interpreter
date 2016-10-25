#include <iostream>
#include "parser.h"

int main() {
	Parser parser;
	/*if (parser.esString("'hola'"))
		std::cout << "Verdadero" << std::endl;
	else
		std::cout << "Falso" << std::endl;*/

	Object *msg = parser.script("'hola' print.");
	//Object *msg = parser.script("'nil'.");
	msg->mostrar("lobby");

	//Object *msg2 = parser.script("'2do string' print.");
	//Object *msg = parser.script("'nil'.");
	//msg2->mostrar("lobby");

	Object *msg3 = parser.script("'2do-string-sin-espacios' print.");
	//Object *msg = parser.script("'nil'.");
	msg3->mostrar("lobby");
	return 0;
}
