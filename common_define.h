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

//Protocolo
const std::string FALSE_BIN = "0";
const std::string TRUE_BIN = "1";

//Parser
const std::string NIL = "nil";
const std::string TRUE = "true";
const std::string FALSE = "false";
const std::string OP_ASIGNACION = ":";
const std::string OP_SLOT_INMUTABLE = "=";
const std::string OP_SLOT_MUTABLE = "<-";
const std::string PUNTO = ".";
const std::string OP_ARG = ":";
const std::string SLOT_LIST_SEP = "|";
const std::string OP_PARENT = "*";
const std::string P_LEFT = "(";
const std::string P_RIGHT = ")";

#endif /* _COMMON_DEFINE_H_ */
