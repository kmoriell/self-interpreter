#include "client_parser_protocolo_workspaces.h"

#include <iostream>
#include <string>
#include "common_define.h"
#include <vector>

ParserProtocoloWorkspaces::ParserProtocoloWorkspaces(
        std::vector<std::string> &workspaces, std::string &cad) :
        workspaces(workspaces), cad(cad) {
    workspaces.clear();
    std::string wkName;
    workspaces.clear();
    while (pCad < (int) cad.size()) {
        wkName = getCampo();
        pCad++; //Salimos del caracter separador
        workspaces.push_back(wkName);
    }
}

std::string ParserProtocoloWorkspaces::getCampo() {
    std::string campo;
    while (cad[pCad] != CHAR_SEPARADOR and pCad < (int) cad.size()) {
        campo += cad[pCad];
        pCad++;
    }
    return campo;
}
