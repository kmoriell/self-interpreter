#include "server_parserProtocoloServidor.h"

#define CHAR_SEPARADOR '@'
const std::string FALSE_BIN = "0";
const std::string TRUE_BIN = "1";

ParserProtocoloServidor::ParserProtocoloServidor(Object* obj) {
	this->obj = obj;
}


std::string ParserProtocoloServidor::getString() {
	std::string cad;
	cad += obj->getName(); //todo agregar nombre real
	cad += CHAR_SEPARADOR;
	cad += obj->getCodeSegment(); //todo agregar nombre real

	Object::slot_map slots = obj->getSlots();

	//Leemos los slots reales
	for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
		std::string slotName = _it->first;
		Object::slot_t slot = _it->second;
		bool esMutable = std::get<1>(slot);
		bool esParent = std::get<2>(slot);
		bool esArgument = std::get<3>(slot);

		cad += CHAR_SEPARADOR;
		cad += slotName;

		cad += CHAR_SEPARADOR;
		cad += FALSE_BIN;

		cad += CHAR_SEPARADOR;
		if (esMutable == false)
			cad += FALSE_BIN;
		else
			cad += TRUE_BIN;

		cad += CHAR_SEPARADOR;
		if (esParent == false)
			cad += FALSE_BIN;
		else
			cad += TRUE_BIN;

		cad += CHAR_SEPARADOR;
		if (esArgument == false)
			cad += FALSE_BIN;
		else
			cad += TRUE_BIN;

		cad += CHAR_SEPARADOR;
		Object* objSlot = (Object*) std::get<0>(slot);
		if (objSlot != nullptr) {
			cad += objSlot->getName(); //todo agregar nombre real

			cad += CHAR_SEPARADOR;
			cad += objSlot->getCodeSegment();
		} else {
			cad += ""; //todo agregar nombre real
			cad += CHAR_SEPARADOR;
			cad += "";
		}



		objSlot->getName();
		//std::cout << dirObj;
	}
	//std::string cad = "Lobby@3.@X@1@0@0@int@3@Y@1@0@0@int@2@cadena@1@0@0@string@'hola mundo'";
	return cad;
}
