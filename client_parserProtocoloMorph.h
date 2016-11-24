#ifndef PARSER_PROTOCOLO_MORPH_H_
#define PARSER_PROTOCOLO_MORPH_H_

#include <string>
#include <vector>
#include "client_morph.h"

class ParserProtocoloMorph {
private:
	Morph &morph;
	std::string &cad;
	int pCad = 0;

public:
	ParserProtocoloMorph(Morph &morph, std::string &cad);
	//ParserProtocoloCliente(std::vector<std::string> &workspaces, std::string &cad);

private:
	std::string getCampo();
};

#endif /* PARSE_RPROTOCOLO_MORPH_H_ */
