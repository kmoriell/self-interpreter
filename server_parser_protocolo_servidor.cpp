#include "server_parser_protocolo_servidor.h"
#include "common_define.h"

ParserProtocoloServidor::ParserProtocoloServidor(Object* obj) {
    this->obj = obj;
}

//todo falta revisar la encapsulacion y tambien hace falta ver el tema mutex aca ya que se leen objetos
std::string ParserProtocoloServidor::getString() {
    std::string cad;
    cad += obj->getName(); //todo agregar nombre real
    cad += CHAR_SEPARADOR;
    cad += obj->getCodeSegment(); //todo agregar nombre real

    Object::slot_map slots = obj->getSlots();
    std::map<std::string, Object::fpointTuple> nativeMethods =
            obj->getNativeMethods();
    //Leemos los slots que apuntan a metodos nativos

    for (auto _it = nativeMethods.begin(); _it != nativeMethods.end(); ++_it) {
        std::string slotNameNative = _it->first;
        Object::fpointTuple tuple = _it->second;
        //Verificamos que el metodo nativo este activo para el objeto
        if (std::get<1>(tuple)) {
            cad += CHAR_SEPARADOR;
            cad += slotNameNative;

            //Indicamos que es metodo nativo
            cad += CHAR_SEPARADOR;
            cad += TRUE_BIN;

            //No es mutable
            cad += CHAR_SEPARADOR;
            cad += FALSE_BIN;

            //No es parent slot
            cad += CHAR_SEPARADOR;
            cad += FALSE_BIN;

            //No es argument slot
            cad += CHAR_SEPARADOR;
            cad += FALSE_BIN;

            //Nombre native method
            cad += CHAR_SEPARADOR;
            cad += NATIVE_METHOD;

            //Vista previa
            cad += CHAR_SEPARADOR;
            cad += COMPLEX_PREVIEW;
        }
    }

    //Leemos los slots que apuntan a objetos (metodos no nativos)
    for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
        std::string slotName = _it->first;
        Object::slot_t slot = _it->second;
        bool esMutable = std::get<1>(slot);
        bool esParent = std::get<2>(slot);
        bool esArgument = std::get<3>(slot);

        cad += CHAR_SEPARADOR;
        cad += slotName;

        //Indicamos que NO es metodo nativo
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

        Object* objSlot = (Object*) std::get<0>(slot);
        if (objSlot != nullptr) {
            cad += CHAR_SEPARADOR;
            cad += objSlot->getName(); //todo agregar nombre real
            cad += CHAR_SEPARADOR;
            cad += objSlot->getCodeSegment();
        } else {
            cad += CHAR_SEPARADOR;
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
