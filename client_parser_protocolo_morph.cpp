#include "client_parser_protocolo_morph.h"

#include <iostream>
#include <string>
#include "common_define.h"
#include "client_morph.h"

ParserProtocoloMorph::ParserProtocoloMorph(Morph &morph, std::string &cad) :
        morph(morph), cad(cad) {
    morph.clear();
    std::string objName = getCampo();
    morph.setObjName(objName);
    pCad++; //Salimos del caracter separador

    std::string codeSegment = getCampo();
    morph.setCodeSegment(codeSegment);
    pCad++; //Salimos del caracter separador

    std::string slotName;
    std::string strNativeMethod;
    bool isNativeMethod;
    std::string strMutable;
    bool isMutable;
    std::string strArgument;
    bool isArgument;
    std::string strParent;
    bool isParent;
    std::string objSlotName;
    std::string objSlotPreview;

    //std::cout << "Cadena: " << cad << std::endl;
    while (pCad < (int) cad.size()) {
        slotName = getCampo();
        pCad++; //Salimos del caracter separador

        strNativeMethod = getCampo();
        if (strNativeMethod == FALSE_BIN)
            isNativeMethod = false;
        else
            isNativeMethod = true;
        pCad++; //Salimos del caracter separador

        strMutable = getCampo();
        if (strMutable == FALSE_BIN)
            isMutable = false;
        else
            isMutable = true;
        pCad++; //Salimos del caracter separador

        strParent = getCampo();
        if (strParent == FALSE_BIN)
            isParent = false;
        else
            isParent = true;
        pCad++; //Salimos del caracter separador

        strArgument = getCampo();
        if (strArgument == FALSE_BIN)
            isArgument = false;
        else
            isArgument = true;
        pCad++; //Salimos del caracter separador

        objSlotName = getCampo();
        pCad++; //Salimos del caracter separador

        objSlotPreview = getCampo();
        pCad++; //Salimos del caracter separador

        morph.addSlot(slotName, isNativeMethod, isMutable, isArgument, isParent,
                objSlotName, objSlotPreview);
    }
}

std::string ParserProtocoloMorph::getCampo() {
    std::string campo;
    while (cad[pCad] != CHAR_SEPARADOR and pCad < (int) cad.size()) {
        campo += cad[pCad];
        pCad++;
    }
    return campo;
}
