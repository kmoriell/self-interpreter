#ifndef PARSER_PROTOCOLO_SERVIDOR_H_
#define PARSER_PROTOCOLO_SERVIDOR_H_

#include <string>
#include "server_object.h"

class ParserProtocoloServidor {
private:
	Object* obj;

public:
	ParserProtocoloServidor(Object* obj);
	std::string getString();
};

#endif /* PARSER_PROTOCOLO_SERVIDOR_H_ */
