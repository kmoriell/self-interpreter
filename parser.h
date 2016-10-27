#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "object.h"

class Parser {
public:
	int pCad;

public:
	std::vector<Object*> run(std::string &cad);

private:
	std::vector<Object*> script(std::string &cad);
	Object* expression(std::string &cad);
	Object* expressionCP(std::string &cad);
	Object* expressionP(std::string &cad);
	Object* keywordMessage(std::string &cad);
	Object* binaryMessage(std::string &cad);
	Object* unaryMessage(std::string &cad);
	Object* receiver(std::string &cad);
	Object* object(std::string &cad);
	Object* slotList(std::string &cad);
	Object* slotNameExtended(std::string &cad);
	Object* constant(std::string &cad);
	bool operador(std::string &cad);

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
	std::string operador(const std::string &cad);

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
