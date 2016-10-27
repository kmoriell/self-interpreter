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

std::vector<Object*> Parser::run(const std::string &cad) {
	std::cout << ">>> " << cad << " <<<" << std::endl;
	pCad = 0;
	std::vector<Object*> objects = script(cad);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->mostrar();
	return objects;
}

std::vector<Object*> Parser::script(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "script pos: " << _pCad << std::endl;
	Object* obj = nullptr;
	std::vector<Object*> objects;
	char cCad;

	while (pCad < cad.size()) {
		cCad = cad[pCad];
		if (((obj = expression(cad)) != nullptr) and (punto(cad)))
			objects.push_back(obj);
		else {
			pCad = _pCad;
			//destruir objeto creado y vaciar el vector
			break;
		}
	}
	return objects;
}

Object * Parser::expression(const std::string & cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "expression pos: " << _pCad << std::endl;
	Object* obj;

	if ((obj = keywordMessage(cad)) != nullptr)
		return obj;
	else if ((obj = binaryMessage(cad)) != nullptr)
		return obj;
	else if ((obj = unaryMessage(cad)) != nullptr)
		return obj;
	else if ((obj = expressionCP(cad)) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

Object * Parser::expressionCP(const std::string & cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "expressionCP pos: " << _pCad << std::endl;
	Object* obj;

	if ((obj = expressionP(cad)) != nullptr)
		return obj;
	else if ((obj = constant(cad)) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

Object * Parser::expressionP(const std::string & cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "expressionP pos: " << _pCad << std::endl;
	Object* obj = nullptr;

	if (pLeft(cad) and ((obj = expression(cad)) != nullptr) and (pRight(cad)))
		return obj;
	pCad = _pCad;
	return obj;
}

//todo
Object * Parser::keywordMessage(const std::string & strKeywordMessage) {
	//std::cout << "keywordMessage pos: " << pCad << std::endl;
	return nullptr;
}

//todo
Object * Parser::binaryMessage(const std::string & cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "binaryMessage pos: " << pCad << std::endl;
	Object* obj = receiver(cad);
	if (obj != nullptr) {
		std::string strOp = operador(cad);
		if (strOp != "") {
			Object* obj2 = expressionCP(cad);
			if (obj2 != nullptr) {
				obj->recvMessage(obj, strOp, std::vector<Object*> { obj2 });
				//Si recvMessage al fallar no devuelve nullptr tengo que hacerlo capturando una excepcion.
				if (obj != nullptr)
					return obj;
			} else {
				//todo destruir obj Receiver
				obj = nullptr;
			}
		} else {
			//aca es donde cambiamos la def de unary_message := (receiver name | receiver)
			return obj;
		}
	}

	pCad = _pCad;
	return obj;
}

Object * Parser::unaryMessage(const std::string & cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "unaryMessage pos: " << _pCad << std::endl;
	Object* obj = receiver(cad);
	if (obj != nullptr) {
		std::string strName = name(cad);
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

Object * Parser::receiver(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "receiver pos: " << _pCad << std::endl;
	Object* obj;
	if ((obj = expressionCP(cad)) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

std::string Parser::name(const std::string &cad) {
	//std::cout << "name pos: " << pCad << std::endl;
	skipSpaces(cad);
	std::string strName = "";
	char cCad = cad[pCad];
	if ('a' <= cCad and cCad <= 'z') {
		pCad++;
		strName += cCad;
		while (pCad < cad.size()) {
			cCad = cad[pCad];
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

//todo //Asi como esta soporta strings con espacios en medio
//No soporta 'hola "'" zaraza' -> falta un detector de doble comilla
std::string Parser::string(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "string pos: " << _pCad << std::endl;
	skipSpaces(cad);
	std::string strString = "";
	bool esString = false;
	char cCad = cad[pCad];
	if ('\'' == cCad) {
		pCad++;
		strString += cCad;
		while (pCad < cad.size() and !esString) {
			cCad = cad[pCad];
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
std::string Parser::number(const std::string &cad) {
	//std::cout << "number pos: " << pCad << std::endl;
	skipSpaces(cad);

	std::string strNumber = "";
	char cCad = cad[pCad];
	while (pCad < cad.size()) {
		cCad = cad[pCad];
		if ('0' <= cCad and cCad <= '9') {
			pCad++;
			strNumber += cCad;
		} else
			break;
	}

	return strNumber;
}

std::string Parser::lowerKeyword(const std::string &cad) {
	//std::cout << "lowerKeyword pos: " << pCad << std::endl;
	skipSpaces(cad);
	std::string strLowerKeyword = "";
	char cCad = cad[pCad];
	if (('a' <= cCad and cCad <= 'z') or (cCad == '_')) {
		pCad++;
		strLowerKeyword += cCad;
		while (pCad < cad.size()) {
			cCad = cad[pCad];
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

std::string Parser::capKeyword(const std::string &cad) {
	//std::cout << "capKeyword pos: " << pCad << std::endl;
	skipSpaces(cad);
	std::string strCapKeyword = "";
	char cCad = cad[pCad];
	if ('A' <= cCad and cCad <= 'Z') {
		pCad++;
		strCapKeyword += cCad;
		while (pCad < cad.size()) {
			cCad = cad[pCad];
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

Object * Parser::object(const std::string & cad) {
	return nullptr;
}

Object * Parser::slotList(const std::string & cad) {
	return nullptr;
}

Object * Parser::slotNameExtended(const std::string & cad) {
	return nullptr;
}

//todo falta name bool
Object * Parser::constant(const std::string & cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "constant pos: " << _pCad << std::endl;
	Object* obj;

	if ((obj = nilObj(cad)) != nullptr)
		return obj;
	else if ((obj = stringObj(cad)) != nullptr)
		return obj;
	else if ((obj = numberObj(cad)) != nullptr)
		return obj;
	else if ((obj = objectObj(cad)) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

std::string Parser::operador(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "operador pos: " << _pCad << std::endl;
	std::string strOp;
	skipSpaces(cad);

	strOp = cad.substr(pCad, 2);
	if (strOp == "==" or strOp == "!=") {
		pCad += 2;
		return strOp;
	}

	strOp = cad.substr(pCad, 1);
	if (strOp == "+" or strOp == "-" or strOp == "*" or strOp == "/") {
		pCad += 1;
		return strOp;
	}

	pCad = _pCad;
	return strOp;
}

void Parser::skipSpaces(const std::string &cad) {
	//std::cout << "skipSpaces pos: " << pCad << std::endl;
	char cCad;
	bool salir = false;
	while (pCad < cad.size() and !salir) {
		cCad = cad[pCad];
		if (cCad == ' ' or cCad == '\t' or cCad == '\n')
			pCad++;
		else
			salir = true;
	}
}

bool Parser::isChar(const std::string &cad, const char cMatch) {
	int _pCad = pCad; //checkpoint
	//std::cout << "isChar pos: " << _pCad << std::endl;
	skipSpaces(cad);
	char cCad = cad[pCad];
	pCad++;

	if (cCad == cMatch)
		return true;

	pCad = _pCad;
	return false;
}

bool Parser::punto(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "punto pos: " << _pCad << std::endl;
	if (isChar(cad, '.'))
		return true;
	pCad = _pCad;
	return false;
}

bool Parser::pLeft(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "pLeft pos: " << _pCad << std::endl;
	if (isChar(cad, '('))
		return true;
	pCad = _pCad;
	return false;
}

bool Parser::pRight(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	//std::cout << "pRight pos: " << _pCad << std::endl;
	if (isChar(cad, ')'))
		return true;
	pCad = _pCad;
	return false;
}

bool Parser::nil(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	skipSpaces(cad);
	std::string candNil = cad.substr(pCad, 5);
	if (candNil == "'nil'") {
		pCad += 5;
		return true;
	}

	pCad = _pCad;
	return false;
}

Object* Parser::nilObj(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces(cad);
	if (nil(cad))
		obj = new Object();
	pCad = _pCad;
	return obj;
}

Object* Parser::stringObj(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces(cad);
	std::string strString = string(cad);

	if (strString != "") {
		obj = new Object();
		obj->setCodeSegment(strString + ".");
		obj->enableNativeMethod(obj, "print");
		//obj->enableNativeMethod(obj, "+");
		//obj->enableNativeMethod(obj, "==");
		//obj->enableNativeMethod(obj, "!=");
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object* Parser::numberObj(const std::string &cad) {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces(cad);
	std::string strNumber = number(cad);

	if (strNumber != "") {
		obj = new Object();
		obj->setCodeSegment(strNumber + ".");
		obj->enableNativeMethod(obj, "print");
		obj->enableNativeMethod(obj, "+");
		obj->enableNativeMethod(obj, "-");
		obj->enableNativeMethod(obj, "*");
		obj->enableNativeMethod(obj, "/");
		//obj->enableNativeMethod(obj, "==");
		//obj->enableNativeMethod(obj, "!=");

		return obj;
	}

	pCad = _pCad;
	return obj;
}

//todo
Object * Parser::objectObj(const std::string & cad) {
	return nullptr;
}

Object * Parser::boolObj(const std::string & cad) {
	return nullptr;
}

/*void Parser::trim(std::string &cad) {
 std::string newCad, x;
 std::istringstream iss(cad);

 while (iss >> std::skipws >> x) {
 newCad += " " + x;
 }

 if (newCad[0] == '\t' || newCad[0] == '\n' || newCad[0] == ' ') {
 cad = newCad.substr(1);
 }
 }


 bool Parser::isName(std::string cad) {
 std::regex regExp("^" + REGEX_NAME + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isString(std::string cad) {
 if (isNil(cad))
 return false;
 std::regex regExp("^" + REGEX_STRING + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isLowerKeyword(std::string cad) {
 std::regex regExp("^" + REGEX_LOWER_KEYWORD + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isCapKeyword(std::string cad) {
 std::regex regExp("^" + REGEX_CAP_KEYWORD + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isNumber(std::string cad) {
 std::regex regExp("^" + REGEX_NUMBER + "$");
 return (std::regex_match(cad, regExp));
 }

 bool Parser::isOperador(std::string cad) {
 return (cad == "+" or cad == "-" or cad == "*" or cad == "/" or cad == "!="
 or cad == "==");
 }*/
