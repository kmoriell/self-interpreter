#ifndef _COMMON_DEFINE_H_
#define _COMMON_DEFINE_H_

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
#define CHAR_SEPARADOR '@'

//Operadores
const std::string OP_SUMA = "+";
const std::string OP_RESTA = "-";
const std::string OP_MULTIPLICACION = "*";
const std::string OP_DIVISION = "/";
const std::string OP_DISTINTO = "!=";
const std::string OP_IGUAL = "==";

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

//Nombres objetos
const std::string NIL_OBJ = "nil";
const std::string BOOLEAN_OBJ = "bool";
const std::string STRING_OBJ = "string";
const std::string NUMBER_OBJ = "number";
const std::string NATIVE_METHOD = "native method";
const std::string COMPLEX_OBJ = "object";

//Otras Constantes
const std::string LOBBY = "lobby";
const std::string SELF = "self";
const std::string COMPLEX_PREVIEW = "...";
const std::string PRINT_METHOD = "print";
const std::string PRINTOBJ_METHOD = "printObj";
const std::string CLONE_METHOD = "clone";
const std::string ADD_SLOTS_METHOD = "_AddSlots";
const std::string REMOVE_SLOTS_METHOD = "_RemoveSlots";

#endif /* _COMMON_DEFINE_H_ */
