#ifndef PARSER_PROTOCOLO_WORKSPACES_H_
#define PARSER_PROTOCOLO_WORKSPACES_H_

#include <string>
#include <vector>

class ParserProtocoloWorkspaces {
private:
	std::vector<std::string> &workspaces;
	std::string &cad;
	int pCad = 0;

public:
	ParserProtocoloWorkspaces(std::vector<std::string> &workspaces, std::string &cad);

	ParserProtocoloWorkspaces(const ParserProtocoloWorkspaces&) = delete;
	ParserProtocoloWorkspaces(ParserProtocoloWorkspaces&&) = delete;

	ParserProtocoloWorkspaces& operator=(const ParserProtocoloWorkspaces&) = delete;
	ParserProtocoloWorkspaces& operator=(ParserProtocoloWorkspaces&&) = delete;
private:
	std::string getCampo();
};

#endif /* PARSE_RPROTOCOLO_WORKSPACES_H_ */
