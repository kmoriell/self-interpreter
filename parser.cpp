#include "parser.h"
#include "object.h"
#include <vector>
#include <tuple>

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


Object* Parser::script(std::string strScript) {
	std::vector<std::string> strExpressions;
	Object* obj = nullptr;

	//Parseo que genera el strExpressions
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
	int tipoExpression = 0;
	std::string strReceiver;

	std::string lower_keyword, strExpressionCP, name, operador;
	std::vector<std::tuple<std::string, std::string> > vTuple;

	//Parseo ti
	//tipoExpression = UNARY_MESSAGE; //todo
	//strReceiver = "'hola'"; //todo
	//name = "print"; //todo

	tipoExpression = EXPRESSION_CP; //todo
	strExpressionCP = "'nil'"; //todo

	switch (tipoExpression) {
	case 0:
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
	int tipoConstant;
	Object* obj = nullptr;

	//Parseo...
	//tipoConstant = STRING; //todo
	tipoConstant = NIL; //todo

	switch (tipoConstant) {
	case NUMBER: {
		std::string strNumber = strConstant;
		//obj = number(strNumber);
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
	obj->setCodeSegment(strString);

	//TODO: agregar slot para print.
	obj->_AddSlots("print", nullptr, false, false, true);

	return obj;
}

Object* Parser::nilObj() {
	Object *obj = new Object();
	obj->setName("nil");

	Object *objTmp = new Object();
	objTmp->setName("pepito");
	objTmp->setCodeSegment("'pepito' print.");
	obj->_AddSlots("metodo0", objTmp, true, false, false);
	return obj;
}

/*
 main() {
 std::string strScript = ... obtiene archivo;
 Object* object = script(strScript);
 script(object->getCodeSegment());
 }

 std::string number(std::string strNumber) {
 //parsing strNumber...
 //parsing "3"...
 //vSlotList = ""; //Aca hay que parsear y devolver un vector todo lo que esta entre los dos || que termina en .
 slotList(vSlotList);
 strScript = "3." //se parseo hasta que quedo script
 }*/
