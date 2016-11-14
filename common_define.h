#ifndef _COMMON_DEFINE_H_
#define _COMMON_DEFINE_H_
#define CHAR_SEPARADOR '@'

// Mensajes de servidor
#define ERRORMESSAGE -1
#define OKMESSAGE 0x00
#define AVAILABLEMESSAGE 0x01

// Comandos de cliente
#define LOADCOMMAND 0x10
#define AVAILABLECOMMAND 0x11
#define NEWCOMMAND 0x12
#define DELETECOMMAND 0x13
#define CLOSECOMMAND 0x14

#define SENDCOMMAND 0x15

const std::string FALSE = "0";
const std::string TRUE = "1";

#endif /* _COMMON_DEFINE_H_ */
