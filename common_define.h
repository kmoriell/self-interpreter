#ifndef _COMMON_DEFINE_H_
#define _COMMON_DEFINE_H_

// Mensajes de servidor
#define ERRORMESSAGE 0x50
#define OKMESSAGE 0x00
#define AVAILABLEMESSAGE 0x01

// Comandos que envia cliente y recibe servidor

//Los comandos 0x0<x> se ejecutan en el contexto lobby
#define EXEC_LOBBY_CMD 0x01
#define SHOW_LOBBY 0x02

//Los comandos 0x[1,2]<x> se ejecutan en el contexto local del cliente
#define EXEC_LOCAL_CMD 0x11
#define SET_OBJ_NAME 0x12
#define SET_SLOT_NAME 0x13
#define ADD_SLOT_NIL 0x14
#define ADD_SLOT_BOOL 0x15
#define ADD_SLOT_NUMBER 0x16
#define ADD_SLOT_STRING 0x17
#define ADD_SLOT_OBJECT 0x18
#define REMOVE_SLOT 0x19
#define SWAP_MUTABILITY 0x20
#define ADD_ARGUMENT_SLOT 0x21
#define ADD_PARENT_SLOT 0x22
#define SET_CODESEGMENT 0x23

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
