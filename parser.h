#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "object.h"
#include "virtualMachine.h"

class Parser {
public:
	Parser(std::string &cad);
	std::vector<Object*> run();
	void setContext(Object* context);

private:
	Object* context;
	std::string &cad;
	int pCad;
	bool debug = false;
	int flagExecute;
	VirtualMachine vm;

	std::vector<Object*> script();
	Object* expression();
	Object* expressionCP();
	Object* expressionP();
	Object* keywordMessage();
	Object* binaryMessage();
	void pepito(std::string &strName, Object* &obj);
	Object * recibirMensaje(Object* obj, std::string strName, std::vector<Object*> &args);
	Object * recibirMensaje2(Object* obj, std::string strName, std::vector<Object*> &args);
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
	Object* nameObj(Object* &context);

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
