#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "object.h"

class Parser {
public:
	int pCad;

public:
	std::vector<Object*> run(const std::string &cad);

private:
	std::vector<Object*> script(const std::string &cad);
	Object* expression(const std::string &cad);
	Object* expressionCP(const std::string &cad);
	Object* expressionP(const std::string &cad);
	Object* keywordMessage(const std::string &cad);
	Object* binaryMessage(const std::string &cad);
	Object* unaryMessage(const std::string &cad);
	Object* receiver(const std::string &cad);
	Object* object(const std::string &cad);
	Object* slotList(const std::string &cad);
	Object* slotNameExtended(const std::string &cad);
	Object* constant(const std::string &cad);
	std::string operador(const std::string &cad);

	void skipSpaces(const std::string &cad);
	bool isChar(const std::string &cad, const char cMatch);
	bool punto(const std::string &cad);
	bool pLeft(const std::string &cad);
	bool pRight(const std::string &cad);

	Object* nilObj(const std::string &cad);
	Object* stringObj(const std::string &cad);
	Object* numberObj(const std::string &cad);
	Object* objectObj(const std::string &cad);
	Object* boolObj(const std::string &cad);

	bool nil(const std::string &cad);
	std::string name(const std::string &cad);
	std::string lowerKeyword(const std::string &cad);
	std::string capKeyword(const std::string &cad);
	std::string string(const std::string &cad);
	std::string number(const std::string &cad);

	/*void trim(std::string &cad);
	bool isNil(std::string &cad);
	bool isName(std::string cad);
	bool isString(std::string cad);
	bool isNumber(std::string cad);
	bool isLowerKeyword(std::string cad);
	bool isCapKeyword(std::string cad);
	bool isOperador(std::string cad);*/
};

#endif /* PARSER_H_ */
