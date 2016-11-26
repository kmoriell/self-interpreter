#ifndef SERVER_PARSER_H_
#define SERVER_PARSER_H_

#include <string>

#include "server_object.h"
#include "server_virtualMachine.h"

class Parser {
private:
	Object* context;
	std::string cad;
	uint32_t pCad;
	bool debug = false;
	int flagExecute;
	VirtualMachine &vm;

public:
	Parser(VirtualMachine &vm);
	std::vector<Object*> run(std::string &cad);
	void setContext(Object* context);


private:
	std::vector<Object*> script();
	Object* expression();
	Object* expressionCP();
	Object* expressionP();
	Object* keywordMessage();
	Object* binaryMessage();
	Object * recibirMensaje(Object* obj, std::string strName,
			std::vector<Object*> &args);
	Object* unaryMessage();
	Object* receiver();
	bool slotList(Object* objContenedor);
	bool slotNameExtended(int &tipoSlot, std::string &strName);
	Object* constant();
	bool operador(std::string &strOperador);
	bool operadorSlot(std::string &strOperadorSlot);
	bool lowerKeyword(std::string &strLowerKeyword);
	bool capKeyword(std::string &strCapKeyword);

	void skipSpaces();
	bool isString(const std::string strMatch);

	bool isLowercaseLetter();
	bool isUppercaseLetter();
	bool isLetter();
	bool isSign();
	bool isDigit();
	bool isAlpha();

	//Devuelven los objetos, ya sea creandolos
	//o instanciandolos.
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
	bool number(float &number);
};

#endif /* SERVER_PARSER_H_ */
