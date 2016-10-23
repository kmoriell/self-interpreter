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
};

#endif /* PARSER_H_ */
