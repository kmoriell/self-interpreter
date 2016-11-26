#ifndef _COMMON_DEFINE_H_
#define _COMMON_DEFINE_H_

// Mensajes de servidor
#define ERRORMESSAGE 0x50
#define OK_MSG_MORPH 0x00
#define OK_MSG_SELECT_WKS 0x01

// Comandos que envia cliente y recibe servidor

//Los comandos 0x0<x> se ejecutan en el contexto lobby
#define EXEC_LOBBY_CMD 0x01
#define SHOW_LOBBY 0x02

//Los comandos 0x[1]<x> se ejecutan en el contexto local del cliente
#define EXEC_LOCAL_CMD 0x10
#define EXEC_REFRESH 0x11
#define SET_OBJ_NAME 0x12
#define SET_CODESEGMENT 0x13
#define ADD_SLOT 0x14
#define REMOVE_SLOT 0x15
#define SWAP_MUTABILITY 0x16
#define GET_SLOT_OBJ 0x17
#define GO_BACK 0x18

//Los comandos 0x[2]<x> comandos relacionados a solicitudes de Workspaces
#define AVAILABLE_WKS 0x20
#define LOAD_WK 0x21
#define NEW_WK 0x22
#define DELETE_WK 0x23
#define CLOSE_WK 0x24

//Protocolo
const std::string FALSE_BIN = "0";
const std::string TRUE_BIN = "1";
#define CHAR_SEPARADOR '~'

//Operadores
const std::string OP_SUMA = "+";
const std::string OP_RESTA = "-";
const std::string OP_MULTIPLICACION = "*";
const std::string OP_DIVISION = "/";
const std::string OP_DISTINTO = "!=";
const std::string OP_IGUAL = "==";

//Parser
const std::string NIL = "nil";
const std::string TRUE_STR = "true";
const std::string FALSE_STR = "false";
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
const std::string BOOLEAN_OBJ = "boolean";
const std::string STRING_OBJ = "string";
const std::string NUMBER_OBJ = "number";
const std::string NATIVE_METHOD = "native";
const std::string COMPLEX_OBJ = "object";

//Otras Constantes
const std::string LOBBY = "lobby";
#define ID_LOBBY 0
const std::string SELF = "self";
const std::string COMPLEX_PREVIEW = "...";

//Metodos nativos
const std::string PRINT_METHOD = "print";
const std::string PRINTOBJ_METHOD = "printObj";
const std::string CLONE_METHOD = "clone";
const std::string ADD_SLOTS_METHOD = "_AddSlots";
const std::string REMOVE_SLOTS_METHOD = "_RemoveSlots";
const std::string COLLECT_METHOD = "collect";


//Valores defaults para cuando se crean slots con objetos tipados
const bool BOOLEAN_OBJ_DEFAULT = false;
const float NUMBER_OBJ_DEFAULT = 0;
const std::string STRING_OBJ_DEFAULT = "'insertar Cadena'";

//Server
#define SERVER_QUIT_CHAR 'q'

#endif /* _COMMON_DEFINE_H_ */
