#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "object.h"

class Parser {
public:
	Object* script(std::string strScript);
	Object* expression(std::string strExpression);
	Object* expressionCP(std::string strExpressionCP);
	Object* constant(std::string strConstant);
	Object* unaryMessage(Object* receiver, std::string name);

	Object* stringObj(std::string strString);
	Object* numberObj(std::string strNumber);
	Object* nilObj();

	bool isNil(std::string cad);
	bool isName(std::string cad);
	bool isString(std::string cad);
	bool isNumber(std::string cad);
	bool isLowerKeyword(std::string cad);
	bool isCapKeyword(std::string cad);
	bool isReceiver(std::string cad); //todo
	bool isUnaryMessage(std::string cad, std::string &receiverCandidate, std::string &nameCandidate);
};

#endif /* PARSER_H_ */
