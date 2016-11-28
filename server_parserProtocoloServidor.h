#ifndef PARSER_PROTOCOLO_SERVIDOR_H_
#define PARSER_PROTOCOLO_SERVIDOR_H_

#include <string>
#include "server_object.h"

/** Esta clase se encarga de generar una cadena con el formato por protocolo
 * en funcion de un objeto dado por el servidor para que la misma sea enviada
 * por el ProxyClient al cliente.
 *
 */
class ParserProtocoloServidor {
private:
    ///Objeto con el que se genera la cadena
    Object* obj;

public:
    /** Constructor
     * @param obj Objeto con el que se genera la cadena
     *
     */
    ParserProtocoloServidor(Object* obj);

    /** Constructor por copia deshabilitado
     */
    ParserProtocoloServidor(const ParserProtocoloServidor&) = delete;
    /** Constructor por movimiento deshabilitado
     */
    ParserProtocoloServidor(ParserProtocoloServidor&&) = delete;
    /** Operador de asignacion deshabilitado
     */
    ParserProtocoloServidor& operator=(const ParserProtocoloServidor&) = delete;
    /** Operador de asignacion por moviemiento deshabilitado
     */
    ParserProtocoloServidor& operator=(ParserProtocoloServidor&&) = delete;
    /** Genera la cadena por protocolo en funcion del objeto obj
     * y la retorna.
     */
    std::string getString();
};

#endif /* PARSER_PROTOCOLO_SERVIDOR_H_ */
