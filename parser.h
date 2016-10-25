#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "object.h"

class Parser {
public:
	Object* run(std::string cad);

private:
	bool isNil(std::string cad);
	bool isName(std::string cad);
	bool isString(std::string cad);
	bool isNumber(std::string cad);
	bool isLowerKeyword(std::string cad);
	bool isCapKeyword(std::string cad);
	bool isOperador(std::string cad);

	Object* nilObj(std::string strNil);
	Object* stringObj(std::string strString);
	Object* numberObj(std::string strNumber);
	Object* objectObj(std::string strObject);

	Object* script(std::string strScript);
	Object* expression(std::string strExpression);
	Object* expressionCP(std::string strExpressionCP);
	Object* expressionP(std::string strExpressionCP);
	Object* receiver(std::string strReceiver);
	Object* constant(std::string strConstant);
	Object* unaryMessage(std::string strUnaryMessage);
	Object* binaryMessage(std::string strBinaryMessage);
	Object* keywordMessage(std::string strKeywordMessage);
	Object* object(std::string strObject);
	Object* slotList(std::string strSlotList);
	Object* slotNameExtended(std::string strSlotNameExtended);
};

#endif /* PARSER_H_ */
