#ifndef PARSER_PROTOCOLO_CLIENTE_H_
#define PARSER_PROTOCOLO_CLIENTE_H_

#include <string>
#include "client_morph.h"

class ParserProtocoloCliente {
private:
	Morph &morph;
	std::string &cad;
	int pCad = 0;

public:
	ParserProtocoloCliente(Morph &morph, std::string &cad);

private:
	std::string getCampo();
};

#endif /* PARSE_RPROTOCOLO_CLIENTE_H_ */
