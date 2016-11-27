#ifndef PARSER_PROTOCOLO_SERVIDOR_H_
#define PARSER_PROTOCOLO_SERVIDOR_H_

#include <string>
#include "server_object.h"

class ParserProtocoloServidor {
private:
    Object* obj;

public:
    ParserProtocoloServidor(Object* obj);
    ParserProtocoloServidor(const ParserProtocoloServidor&);
    ParserProtocoloServidor(ParserProtocoloServidor&&);

    ParserProtocoloServidor& operator=(const ParserProtocoloServidor&);
    ParserProtocoloServidor& operator=(ParserProtocoloServidor&&);
    std::string getString();
};

#endif /* PARSER_PROTOCOLO_SERVIDOR_H_ */
