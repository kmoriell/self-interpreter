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

Object* Parser::run(std::string cad){
	std::cout << ">>> " << cad << std::endl;

	std::string newCad, x;
	std::istringstream iss(cad);

	while (iss >> std::skipws >> x) {
	    newCad += " " + x;
	}

	if (newCad[0] == '\t' || newCad[0] == '\n' || newCad[0] == ' ') {
	  newCad = newCad.substr(1);
	}

	Object* obj;
	if ((obj = script(cad)) != nullptr)
		return obj;
	else
		throw std::runtime_error("Cadena: '" + cad + "' inválida. \n");
}

bool Parser::isNil(std::string cad) {
	std::regex regExp("^" + REGEX_NIL + "$");
	return (std::regex_match(cad, regExp));
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
	return (cad == "+" or cad == "-" or cad == "*" or cad == "/" or cad == "!=" or cad == "==");
}

Object* Parser::nilObj(std::string strNil) {
	Object *obj = nullptr;
	if (isNil(strNil))
		obj = new Object();
	return obj;
}

Object* Parser::stringObj(std::string strString) {
	Object *obj = nullptr;
	if (isString(strString)) {
		obj = new Object();
		obj->setCodeSegment(strString + ".");
		obj->enableNativeMethod(obj, "print");
	}
	return obj;
}

Object* Parser::numberObj(std::string strNumber) {
	Object *obj = nullptr;
	if (isNumber(strNumber)) {
		obj = new Object();
		obj->setCodeSegment(strNumber + ".");
		obj->enableNativeMethod(obj, "print");
	}
	return obj;
}

//todo
Object* Parser::objectObj(std::string strObject) {
	return nullptr;
}


//todo hardcode
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
	if ((obj = unaryMessage(strExpression)) != nullptr)
		return obj;
	else if ((obj = binaryMessage(strExpression)) != nullptr)
		return obj;
	else if ((obj = keywordMessage(strExpression)) != nullptr)
		return obj;
	else if ((obj = expressionCP(strExpression)) != nullptr)
		return obj;
	return obj;
}

Object* Parser::receiver(std::string strReceiver) {
	Object* obj;
	if ((obj = expressionCP(strReceiver)) != nullptr)
		return obj;
	return obj;
}

//todo
Object* Parser::expressionP(std::string strExpressionP) {
	Object* obj;
	if ((obj = expression(strExpressionP)) != nullptr)
		return obj;
	return obj;
}

Object* Parser::expressionCP(std::string strExpressionCP) {
	Object* obj = nullptr;
	if ((obj = constant(strExpressionCP)) != nullptr)
		return obj;
	else {
		bool p0 = (strExpressionCP.substr(0, 1) == "(");
		bool pf = (strExpressionCP.substr(strExpressionCP.size()-1, 1) == ")");
		std::string strExpressionP = strExpressionCP.substr(1, strExpressionCP.size()-2);
		if (p0 and pf and ((obj = expressionP(strExpressionP)) != nullptr))
			return obj;
	}
	return obj;
}

Object* Parser::constant(std::string strConstant) {
	Object* obj = nullptr;
	if ((obj = nilObj(strConstant)) != nullptr)
		return obj;
	else if ((obj = stringObj(strConstant)) != nullptr)
		return obj;
	else if ((obj = numberObj(strConstant)) != nullptr)
		return obj;
	else if ((obj = objectObj(strConstant)) != nullptr)
		return obj;
	return obj;
}

//todo hardcode
Object* Parser::unaryMessage(std::string strUnaryMessage) {
	//strName es la ultima palabra
	//strReceiver el resto
	/*std::string strName, strReceiver;
	std::istringstream iss(strUnaryMessage);
	iss >> std::noskipws;
	//std::string candidatoReceiver, candidatoName;
	iss >> std::ws >> strReceiver >> std::ws >> strName;*/

	int parenthesis_count = 0;
	int charCount = 0;

	std::string strReceiver, strName;

	for (char _char : strUnaryMessage) {
	  if ((_char == ' ' ) && parenthesis_count == 0 && charCount > 0){
	    strName = strUnaryMessage.substr(charCount + 1);
	    break;
	  }
	  if (_char == '(')
	    parenthesis_count++;
	  else if(_char == ')')
	    parenthesis_count--;

	  strReceiver.push_back(_char);
	  charCount++;
	}

	Object* objReceiver;
	if ((objReceiver = receiver(strReceiver)) != nullptr and isName(strName))
		return objReceiver->recvMessage(objReceiver, strName,
			std::vector<Object*> { });
	return objReceiver;
}

//todo
Object* Parser::binaryMessage(std::string strBinaryMessage) {
	return nullptr;
}

//todo
Object* Parser::keywordMessage(std::string strKeywordMessage) {
	return nullptr;
}
