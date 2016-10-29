#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "object.h"

class Parser {
public:
	std::vector<Object*> run(std::string &cad);
	void setContext(Object* context);

private:
	Object* context;
  std::string *cad;
  int pCad;
  bool debug = false;
  int flagExecute;

	std::vector<Object*> script();
	Object* expression();
	Object* expressionCP();
	Object* expressionP();
	Object* keywordMessage();
	Object* binaryMessage();
	Object* unaryMessage();
	Object* receiver();
	//Object* object();
	bool slotList(Object* objContenedor);
	bool slotNameExtended(int &tipoSlot, std::string &strName);
	Object* constant();
	bool operador(std::string &strOperador);
	bool operadorSlot(std::string &strOperadorSlot);
	bool lowerKeyword(std::string &strLowerKeyword);
	//bool capKeyword(std::string &strCapKeyword);

	void skipSpaces();
	bool isString(const std::string strMatch);

	Object* nilObj();
	Object* boolObj();
	Object* stringObj();
	Object* numberObj();
	Object* objectObj();
	Object* nameObj();

	bool nil();
	bool isTrue();
	bool isFalse();
	bool name(std::string &strName);
	std::string string();
	std::string number();

	/*void trim(std::string &cad);*/
	/*bool isNil(const std::string &cad);
	bool isName(const std::string cad);
	bool isString(const std::string cad);
	bool isNumber(const std::string cad);
	bool isLowerKeyword(const std::string cad);
	bool isCapKeyword(const std::string cad);*/
};

#endif /* PARSER_H_ */
