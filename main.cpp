#include <iostream>
#include "parser.h"

int main() {
	Parser parser;
	//Object *msg = parser.script("'hola' print.");
	Object *msg = parser.script("'nil'.");
	msg->mostrar();
	return 0;
}
