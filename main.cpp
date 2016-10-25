#include <iostream>
#include "parser.h"

int main() {
	Parser parser;
	/*if (parser.esString("'hola'"))
		std::cout << "Verdadero" << std::endl;
	else
		std::cout << "Falso" << std::endl;*/

	Object *msg = parser.script("3 print.");
	msg->mostrar();

	//Object *msg2 = parser.script("'2do string' print.");
	//Object *msg = parser.script("'nil'.");
	//msg2->mostrar("lobby");

	Object *msg3 = parser.script("-5 print.");
	msg3->mostrar();

	Object *msg4 = parser.script("-10.10 print.");
	msg4->mostrar();
	return 0;
}
