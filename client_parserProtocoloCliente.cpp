#include "client_parserProtocoloCliente.h"

ParserProtocoloCliente::ParserProtocoloCliente(Morph &morph, std::string &cad) : morph(morph), cad(cad) {
	std::string objName = getCampo();
	morph.setObjName(objName);
	pCad++; //Salimos del caracter separador

	std::string codeSegment = getCampo();
	morph.setCodeSegment(codeSegment);
	pCad++; //Salimos del caracter separador

	std::string slotName;
	std::string strMutable;
	bool isMutable;
	std::string strArgument;
	bool isArgument;
	std::string strParent;
	bool isParent;
	std::string objSlotName;
	std::string objSlotPreview;

	while(pCad<cad.size()) {
		slotName = getCampo();
		pCad++; //Salimos del caracter separador

		strMutable = getCampo();
		if (strMutable == FALSE)
			isMutable = false;
		else
			isMutable = true;
		pCad++; //Salimos del caracter separador

		strParent = getCampo();
		if (strParent == FALSE)
			isParent = false;
		else
			isParent = true;
		pCad++; //Salimos del caracter separador

		strArgument = getCampo();
		if (strArgument == FALSE)
			isArgument = false;
		else
			isArgument = true;
		pCad++; //Salimos del caracter separador

		objSlotName = getCampo();
		pCad++; //Salimos del caracter separador

		objSlotPreview = getCampo();
		pCad++; //Salimos del caracter separador

		morph.addSlot(slotName,isMutable,isArgument,isParent,objSlotName,objSlotPreview);
	}

	morph.mostrar();
}

std::string ParserProtocoloCliente::getCampo() {
	std::string campo;
	while (cad[pCad] != CHAR_SEPARADOR and pCad<cad.size()) {
		campo += cad[pCad];
		pCad++;
	}
	return campo;
}
