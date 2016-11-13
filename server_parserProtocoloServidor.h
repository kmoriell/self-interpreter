#ifndef PARSER_PROTOCOLO_SERVIDOR_H_
#define PARSER_PROTOCOLO_SERVIDOR_H_

#include <string>
#include "common_object.h"
//#include "common_define.h"

class ParserProtocoloServidor {
private:
	Object* obj;

public:
	ParserProtocoloServidor(Object* obj);
	std::string getString();
};

#endif /* PARSER_PROTOCOLO_SERVIDOR_H_ */
