#include "parser.h"
#include "object.h"
#include <vector>
#include <tuple>
#include <regex>
#include <sstream>
#include <string>
#include <iostream>

const std::string REGEX_NIL = "'nil'";
const std::string REGEX_NAME = "[a-z][[:alnum:]]*";
const std::string REGEX_STRING = "'[^ \'\"]*'";
const std::string REGEX_LOWER_KEYWORD = "'[^ \'\"]*'";
const std::string REGEX_CAP_KEYWORD = "[_A-Z][[:alnum:]]*";
const std::string REGEX_NUMBER = "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?";

const std::string NIL = "nil";
const std::string TRUE = "true";
const std::string FALSE = "false";
const std::string OP_SUMA = "+";
const std::string OP_RESTA = "-";
const std::string OP_MULTIPLICACION = "*";
const std::string OP_DISTINTO = "!=";
const std::string OP_IGUAL = "==";
const std::string OP_ASIGNACION = ":";
const std::string OP_SLOT_INMUTABLE = "=";
const std::string OP_SLOT_MUTABLE = "<-";
const std::string OP_DIVISION = "/";
const std::string FIN_EXPRESSION = ".";
const std::string OP_ARG = ":";
const std::string SLOT_LIST_SEP = "|";
const std::string OP_PARENT = "*";
const std::string P_LEFT = "(";
const std::string P_RIGHT = ")";
const std::string METHOD_PRINT = "print";

std::vector<Object*> Parser::run(std::string &cad) {
	this->cad = &cad;
	this->pCad = 0;
	std::cout << ">>> " << *this->cad << "<<< " << std::endl;
	std::vector<Object*> objects = script();
	return objects;
}

std::vector<Object*> Parser::script() {
	if (debug)
		std::cout << "script pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj = nullptr;
	std::vector<Object*> objects;

	while (pCad < (*cad).size()) {
		if (((obj = expression()) != nullptr) and isString(FIN_EXPRESSION))
			objects.push_back(obj);
		else {
			pCad = _pCad;
			//destruir objeto creado y vaciar el vector
			break;
		}
	}
	return objects;
}

Object * Parser::expression() {
	if (debug)
		std::cout << "expression pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;

	if ((obj = keywordMessage()) != nullptr)
		return obj;
	else if ((obj = binaryMessage()) != nullptr)
		return obj;
	else if ((obj = unaryMessage()) != nullptr)
		return obj;
	else if ((obj = expressionCP()) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

Object * Parser::expressionCP() {
	if (debug)
		std::cout << "expressionCP pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;

	if ((obj = expressionP()) != nullptr)
		return obj;
	else if ((obj = constant()) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

Object * Parser::expressionP() {
	if (debug)
		std::cout << "expressionP pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj = nullptr;

	if (isString(P_LEFT) and ((obj = expression()) != nullptr)
			and isString(P_RIGHT))
		return obj;
	pCad = _pCad;
	return obj;
}

//todo
Object * Parser::keywordMessage() {
	if (debug)
		std::cout << "keywordMessage pos: " << pCad << std::endl;
	return nullptr;
}

Object * Parser::binaryMessage() {
	if (debug)
		std::cout << "binaryMessage pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj = receiver();
	if (obj != nullptr) {
		std::string strOp = operador();
		if (strOp != "") {
			Object* obj2 = expressionCP();
			if (obj2 != nullptr) {
				obj->recvMessage(obj, strOp, std::vector<Object*> { obj2 });
				//todo hay que capturar excepcion del recvMessage, no devuelve nullptr.
				if (obj != nullptr)
					return obj;
			} else {
				//todo destruir obj Receiver
				obj = nullptr;
			}
		} else {
			//hay que matar el objeto creado en el receiver();
			//aca es donde cambiamos la def de unary_message := (receiver name | receiver)
			obj = nullptr;
			pCad = _pCad;
			return obj;
		}
	}
	pCad = _pCad;
	return obj;
}

Object * Parser::unaryMessage() {
	if (debug)
		std::cout << "unaryMessage pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj = receiver();
	if (obj != nullptr) {
		std::string strName = name();
		if (strName != "") {
			obj->recvMessage(obj, strName, std::vector<Object*> { });
			//Si recvMessage al fallar no devuelve nullptr tengo que hacerlo capturando una excepcion.
			if (obj != nullptr)
				return obj;
		} else {
			//aca es donde cambiamos la def de unary_message := (receiver name | receiver)
			return obj;
		}
	}

	pCad = _pCad;
	return obj;
}

Object * Parser::receiver() {
	if (debug)
		std::cout << "receiver pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint;
	Object* obj;
	if ((obj = expressionCP()) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

std::string Parser::name() {
	if (debug)
		std::cout << "name pos: " << pCad << std::endl;

	skipSpaces();
	std::string strName = "";
	char cCad = (*cad)[pCad];
	if ('a' <= cCad and cCad <= 'z') {
		pCad++;
		strName += cCad;
		while (pCad < (*cad).size()) {
			cCad = (*cad)[pCad];
			if (('a' <= cCad and cCad <= 'z') or ('A' <= cCad and cCad <= 'Z')
					or ('0' <= cCad and cCad <= '9')) {
				pCad++;
				strName += cCad;
			} else
				break;
		}
	}
	return strName;
}

//todo //Asi como esta soporta strings con espacios en medio //No soporta 'hola "'" zaraza' -> falta un detector de doble comilla
std::string Parser::string() {
	if (debug)
		std::cout << "string pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();
	std::string strString = "";
	bool esString = false;
	char cCad = (*cad)[pCad];
	if ('\'' == cCad) {
		pCad++;
		strString += cCad;
		while (pCad < (*cad).size() and !esString) {
			cCad = (*cad)[pCad];
			strString += cCad;
			pCad++;
			if ('\'' == cCad)
				esString = true;
		}
	}

	if (!esString) {
		pCad = _pCad;
		strString = "";
	}
	return strString;
}

//todo //Por ahora solo soporta numeros enteros positivos
std::string Parser::number() {
	if (debug)
		std::cout << "number pos: " << pCad << std::endl;

	skipSpaces();
	std::string strNumber = "";
	char cCad = (*cad)[pCad];
	if (cCad == '-' or cCad == '+' or ('0' <= cCad and cCad <= '9')) {
		pCad++;
		strNumber += cCad;

		while (pCad < (*cad).size()) {
			cCad = (*cad)[pCad];
			if ('0' <= cCad and cCad <= '9') {
				pCad++;
				strNumber += cCad;
			} else
				break;
		}
	}

	return strNumber;
}

std::string Parser::lowerKeyword() {
	if (debug)
		std::cout << "lowerKeyword pos: " << pCad << std::endl;

	skipSpaces();
	std::string strLowerKeyword = "";
	char cCad = (*cad)[pCad];
	if (('a' <= cCad and cCad <= 'z') or (cCad == '_')) {
		pCad++;
		strLowerKeyword += cCad;
		while (pCad < (*cad).size()) {
			cCad = (*cad)[pCad];
			if (('a' <= cCad and cCad <= 'z') or ('A' <= cCad and cCad <= 'Z')
					or ('0' <= cCad and cCad <= '9')) {
				pCad++;
				strLowerKeyword += cCad;
			} else
				break;
		}
	}
	return strLowerKeyword;
}

std::string Parser::capKeyword() {
	if (debug)
		std::cout << "capKeyword pos: " << pCad << std::endl;

	skipSpaces();
	std::string strCapKeyword = "";
	char cCad = (*cad)[pCad];
	if ('A' <= cCad and cCad <= 'Z') {
		pCad++;
		strCapKeyword += cCad;
		while (pCad < (*cad).size()) {
			cCad = (*cad)[pCad];
			if (('a' <= cCad and cCad <= 'z') or ('A' <= cCad and cCad <= 'Z')
					or ('0' <= cCad and cCad <= '9')) {
				pCad++;
				strCapKeyword += cCad;
			} else
				break;
		}
	}
	return strCapKeyword;
}

//todo
Object * Parser::object() {
	if (debug)
		std::cout << "object pos: " << pCad << std::endl;

	return nullptr;
}

//todo
Object * Parser::slotList() {
	if (debug)
		std::cout << "slotList pos: " << pCad << std::endl;

	return nullptr;
}

//todo
Object * Parser::slotNameExtended() {
	if (debug)
		std::cout << "slotNameExtended pos: " << pCad << std::endl;

	return nullptr;
}

//todo falta name bool
Object * Parser::constant() {
	if (debug)
		std::cout << "constant pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;

	if ((obj = nilObj()) != nullptr)
		return obj;
	else if ((obj = boolObj()) != nullptr)
		return obj;
	else if ((obj = stringObj()) != nullptr)
		return obj;
	else if ((obj = numberObj()) != nullptr)
		return obj;
	else if ((obj = objectObj()) != nullptr)
		return obj;
	else if ((obj = nameObj()) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

std::string Parser::operador() {
	if (debug)
		std::cout << "operador pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();

	if (isString(OP_SUMA)) {
		return OP_SUMA;
	} else if (isString(OP_RESTA)) {
		return OP_RESTA;
	} else if (isString(OP_MULTIPLICACION)) {
		return OP_MULTIPLICACION;
	} else if (isString(OP_DIVISION)) {
		return OP_DIVISION;
	} else if (isString(OP_DISTINTO)) {
		return OP_DISTINTO;
	} else if (isString(OP_IGUAL)) {
		return OP_IGUAL;
	} else {
		pCad = _pCad;
		return "";
	}
}

void Parser::skipSpaces() {
	//if (debug)
	//	std::cout << "skipSpaces pos: " << pCad << std::endl;

	char cCad;
	bool salir = false;
	while (pCad < (*cad).size() and !salir) {
		cCad = (*cad)[pCad];
		if (cCad == ' ' or cCad == '\t' or cCad == '\n')
			pCad++;
		else
			salir = true;
	}
}

bool Parser::isString(const std::string strMatch) {
	if (debug)
		std::cout << strMatch << " pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();
	bool isMatch = true;

	for (int i = 0; i < strMatch.size(); i++) {
		if ((pCad < (*cad).size()) and (strMatch[i] == (*cad)[pCad]))
			pCad++;
		else
			isMatch = false;
	}

	if (!isMatch)
		int pCad = _pCad;
	return isMatch;
}

Object* Parser::nilObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();

	if (isString(NIL)) {
		obj = new Object();
		obj->setCodeSegment(NIL + FIN_EXPRESSION);
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object* Parser::boolObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();

	if (isString(TRUE)) {
		obj = new Object();
		obj->setCodeSegment(TRUE + FIN_EXPRESSION);
		obj->enableNativeMethod(obj, METHOD_PRINT);
		return obj;
	} else if (isString(FALSE)) {
		obj = new Object();
		obj->setCodeSegment(FALSE + FIN_EXPRESSION);
		obj->enableNativeMethod(obj, METHOD_PRINT);
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object* Parser::stringObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();
	std::string strString = string();

	if (strString != "") {
		obj = new Object();
		obj->setCodeSegment(strString + FIN_EXPRESSION);
		obj->enableNativeMethod(obj, METHOD_PRINT);
		//obj->enableNativeMethod(obj, OP_SUMA);
		//obj->enableNativeMethod(obj, OP_IGUAL);
		//obj->enableNativeMethod(obj, OP_DISTINTO);
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object* Parser::numberObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();
	std::string strNumber = number();

	if (strNumber != "") {
		obj = new Object();
		obj->setCodeSegment(strNumber + FIN_EXPRESSION);
		obj->enableNativeMethod(obj, METHOD_PRINT);
		obj->enableNativeMethod(obj, OP_SUMA);
		obj->enableNativeMethod(obj, OP_RESTA);
		obj->enableNativeMethod(obj, OP_MULTIPLICACION);
		obj->enableNativeMethod(obj, OP_DIVISION);
		//obj->enableNativeMethod(obj, OP_IGUAL");
		//obj->enableNativeMethod(obj, OP_DISTINTO);

		return obj;
	}

	pCad = _pCad;
	return obj;
}

//todo
Object * Parser::objectObj() {
	return nullptr;
}

Object * Parser::nameObj() {
	//Aca deberia hacer un recv del objeto contexto y pedirle el slot name.
	return nullptr;
}

/*void Parser::trim(const std::string cad) {
 std::string newCad, x;
 std::istringstream iss(cad);

 while (iss >> std::skipws >> x) {
 newCad += " " + x;
 }

 if (newCad[0] == '\t' || newCad[0] == '\n' || newCad[0] == ' ') {
 cad = newCad.substr(1);
 }
 }*/

/*bool Parser::isName(const std::string cad) {
 std::regex regExp("^" + REGEX_NAME + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isString(const std::string cad) {
 if (isNil(cad))
 return false;
 std::regex regExp("^" + REGEX_STRING + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isLowerKeyword(const std::string cad) {
 std::regex regExp("^" + REGEX_LOWER_KEYWORD + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isCapKeyword(const std::string cad) {
 std::regex regExp("^" + REGEX_CAP_KEYWORD + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isNumber(const std::string cad) {
 std::regex regExp("^" + REGEX_NUMBER + "$");
 return (std::regex_match(cad, regExp));
 }*/
