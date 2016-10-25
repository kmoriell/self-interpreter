#include "parser.h"
#include "object.h"
#include <vector>
#include <tuple>
#include <regex>
#include <sstream>
#include <string>
#include <iostream>

const int KEYWORD_MESSAGE = 0;
const int BINARY_MESSAGE = 1;
const int UNARY_MESSAGE = 2;
const int EXPRESSION_CP = 3;
const int EXPRESSION_P = 4;
const int CONSTANT = 5;
const int NUMBER = 6;
const int STRING = 7;
const int NIL = 8;
const int NAME = 9;
const int OBJECT = 10;

const std::string REGEX_NIL = "'nil'";
const std::string REGEX_NAME = "^[a-z][[:alnum:]]*$";
const std::string REGEX_STRING = "^'[^ \'\"]*'$";
const std::string REGEX_LOWER_KEYWORD = "^'[^ \'\"]*'$";
const std::string REGEX_CAP_KEYWORD = "^[_A-Z][[:alnum:]]*$";
const std::string REGEX_NUMBER = "^((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?$";

bool Parser::isNil(std::string cad) {
	std::regex regExp(REGEX_NIL);
	return (std::regex_match(cad, regExp));
}

bool Parser::isName(std::string cad) {
	std::regex regExp(REGEX_NAME);
	return (std::regex_match(cad, regExp));
}

bool Parser::isString(std::string cad) {
	if (isNil(cad))
		return false;
	std::regex regExp(REGEX_STRING);
	return (std::regex_match(cad, regExp));
}

bool Parser::isLowerKeyword(std::string cad) {
	std::regex regExp(REGEX_LOWER_KEYWORD);
	return (std::regex_match(cad, regExp));
}

bool Parser::isCapKeyword(std::string cad) {
	std::regex regExp(REGEX_CAP_KEYWORD);
	return (std::regex_match(cad, regExp));
}

bool Parser::isNumber(std::string cad) {
	std::regex regExp(REGEX_NUMBER);
	return (std::regex_match(cad, regExp));
}

//todo
bool Parser::isObject(std::string cad) {
	return false;
}

bool Parser::isExpression(std::string cad) {
	return false;
}

bool Parser::isExpressionP(std::string cad, std::string &strExpression) {
	bool p0 = (cad.substr(0, 1) == "(");
	bool pf = (cad.substr(cad.size()-1, 1) == ")");
	std::string tmp = cad.substr(1, cad.size()-2);
	if (p0 and pf and isExpression(tmp)) {
		strExpression = tmp;
		return true;
	} else
		return false;
}

bool Parser::isExpressionCP(std::string cad) {
	std::string strExpression;
	return (isConstant(cad) or isExpressionP(cad, strExpression));
}

bool Parser::isReceiver(std::string cad) {
	return isExpressionCP(cad);
}

bool Parser::isConstant(std::string cad) {
	return (isNil(cad) or isName(cad) or isString(cad) or isNumber(cad) or isObject(cad));
}

//No funciona para receiver complejo
bool Parser::isUnaryMessage(std::string cad, std::string &receiverCandidate,
		std::string &nameCandidate) {
	std::istringstream iss(cad);
	iss >> std::noskipws;
	//std::string candidatoReceiver, candidatoName;
	iss >> std::ws >> receiverCandidate >> std::ws >> nameCandidate;

	if (isName(nameCandidate) and isReceiver(receiverCandidate))
		return true;
	else
		return false;
}

Object* Parser::script(std::string strScript) {
	std::vector<std::string> strExpressions;
	Object* obj = nullptr;

	//todo Parseo que genera el strExpressions
	strExpressions.push_back(strScript); // TODO: NO VA

	for (auto strExpression : strExpressions) {
		//Sacamos el . del final
		strExpression = strExpression.substr(0, strExpression.size() - 1);
		obj = expression(strExpression);
	}
	return obj;
}

Object* Parser::expression(std::string strExpression) {
	Object* obj = nullptr;
	int tipoExpression = -1;
	std::string strReceiver;

	std::string lower_keyword, strExpressionCP, name, operador;
	std::vector<std::tuple<std::string, std::string> > vTuple;

	//Parseo ti
	if (isUnaryMessage(strExpression, strReceiver, name))
		tipoExpression = UNARY_MESSAGE;

	//todo: isExpressionCP()
	//todo: binary
	//todo: isExpressionCP()
	//todo: keyword

	switch (tipoExpression) {
	case KEYWORD_MESSAGE:
		//obj = keywordMessage(expresionCP(strReceiver), lower_keyword, expressionCP(strExpressionCP), vTuple);
		break;
	case BINARY_MESSAGE:
		//obj = binaryMessage(expressionCP(strReceiver), operador, strExpressionCP);
		break;
	case UNARY_MESSAGE:
		obj = unaryMessage(expressionCP(strReceiver), name);
		break;
	case EXPRESSION_CP:
		obj = expressionCP(strExpressionCP);
		break;
	}
	return obj;
}

Object* Parser::expressionCP(std::string strExpressionCP) {
	int tipoExpressionCP = 0;
	Object* obj = nullptr;

	//Parseo..
	tipoExpressionCP = CONSTANT; // TODO: no va

	switch (tipoExpressionCP) {
	case EXPRESSION_P: {
		//Sacamos los ( )
		std::string strExpressionP = strExpressionCP.substr(1,
				strExpressionCP.size() - 2);
		obj = expression(strExpressionP);
		break;
	}
	case CONSTANT: {
		std::string strConstant = strExpressionCP;
		obj = constant(strConstant);
		break;
	}
	}
	return obj;
}

Object* Parser::constant(std::string strConstant) {
	int tipoConstant = -1;
	Object* obj = nullptr;

	//Parseo...
	if (isString(strConstant))
		tipoConstant = STRING;

	if (isNil(strConstant))
		tipoConstant = NIL;

	if (isName(strConstant))
		tipoConstant = NAME;

	if (isNumber(strConstant))
		tipoConstant = NUMBER;

	if (isObject(strConstant))
		tipoConstant = OBJECT;

	if (tipoConstant == -1)
		throw std::runtime_error(
				"ERROR: " + strConstant + " no es una constante.\n");

	switch (tipoConstant) {
	case NUMBER: {
		std::string strNumber = strConstant;
		obj = numberObj(strNumber);
		break;
	}
	case STRING: {
		std::string strString = strConstant;
		obj = stringObj(strString);
		break;
	}
	case NIL:
		obj = nilObj();
		break;
	case NAME:
		//Hay que hacer un lookup y devolver el objeto encontrado
		break;
	case OBJECT: {
		std::string strObject = strConstant;
		//obj = object(strObject);
		break;
	}
	}
	return obj;
}

Object* Parser::unaryMessage(Object* receiver, std::string name) {
	Object* message = receiver->recvMessage(receiver, name,
			std::vector<Object*> { });
	//message = (|*print|)
	return message;
	//estoy retornando (||'hola'.)
}

Object* Parser::stringObj(std::string strString) {
	Object *obj = new Object();
	obj->setCodeSegment(strString+".");
	obj->enableNativeMethod(obj, "print");
	return obj;
}

Object* Parser::numberObj(std::string strNumber) {
	Object *obj = new Object();
	obj->setCodeSegment(strNumber+".");
	obj->enableNativeMethod(obj, "print");
	return obj;
}

Object* Parser::nilObj() {
	Object *obj = new Object();
	return obj;
}

//todo
Object* objectObj(std::string strObject) {
	return nullptr;
}
