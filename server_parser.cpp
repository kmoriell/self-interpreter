#include "server_parser.h"

#include <vector>
#include <tuple>
#include <regex>
#include <sstream>
#include <string>
#include <iostream>
#include "server_object.h"
#include "common_define.h"

Parser::Parser(VirtualMachine &vm) :
		vm(vm) {
	this->pCad = 0;
	this->flagExecute = 0;
	this->context = nullptr;
}

std::vector<Object*> Parser::run(std::string &cad) {
	this->cad = cad;
	//std::cout << "Contexto: " << this->context << "<<< " << std::endl;
	//std::cout << ">>> " << *this->cad << "<<< " << std::endl;
	std::vector<Object*> objects = script();
	return objects;
}

std::vector<Object*> Parser::script() {
	if (debug)
		std::cout << "script pos: " << pCad << std::endl;
	flagExecute++;
	//int _pCad = pCad; //checkpoint
	Object* obj = nullptr;
	std::vector<Object*> objects;

	int pLastExpression = pCad;
	while (pCad < cad.size()) {
		if (((obj = expression()) != nullptr) and isString(PUNTO)) {
			objects.push_back(obj);
			pLastExpression = pCad;
		} else {
			pCad = pLastExpression;
			//destruir objeto creado y vaciar el vector
			break;
		}
	}
	flagExecute--;
	return objects;
}

Object * Parser::expression() {
	if (debug)
		std::cout << "expression pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;

	if ((obj = keywordMessage()) != nullptr)
		return obj;
	else if ((obj = binaryMessage()) != nullptr)
		return obj;
	else if ((obj = unaryMessage()) != nullptr)
		return obj;
	else if ((obj = expressionCP()) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

Object * Parser::expressionCP() {
	if (debug)
		std::cout << "expressionCP pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;

	if ((obj = expressionP()) != nullptr)
		return obj;
	else if ((obj = constant()) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

Object * Parser::expressionP() {
	if (debug)
		std::cout << "expressionP pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj = nullptr;

	if (isString(P_LEFT) and ((obj = expression()) != nullptr)
			and isString(P_RIGHT))
		return obj;
	pCad = _pCad;
	return obj;
}

Object * Parser::keywordMessage() {
	if (debug)
		std::cout << "keywordMessage pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;
	Object* arg;
	std::string strLowerKeyword;

	if ((obj = receiver()) != nullptr and lowerKeyword(strLowerKeyword)
			and isString(OP_ARG) and (arg = expressionCP()) != nullptr) {
		//std::cout << "soy binaryMessage pos: " << pCad << std::endl;
		std::vector<Object*> args = { arg };
		obj = recibirMensaje(obj, strLowerKeyword, args);
		if (obj != nullptr)
			return obj;
	}
	pCad = _pCad;

	if (lowerKeyword(strLowerKeyword) and isString(OP_ARG) and (arg =
			expressionCP()) != nullptr) {
		//std::cout << "soy binaryMessage pos: " << pCad << std::endl;
		std::vector<Object*> args = { arg };
		obj = recibirMensaje(context, strLowerKeyword, args);
		if (obj != nullptr)
			return obj;
	}
	pCad = _pCad;

	return nullptr;
}

Object * Parser::binaryMessage() {
	if (debug)
		std::cout << "binaryMessage pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;
	Object* arg;
	std::string strOp;

	if ((obj = receiver()) != nullptr and operador(strOp) and (arg =
			expressionCP()) != nullptr) {
		//std::cout << "soy binaryMessage pos: " << pCad << std::endl;
		std::vector<Object*> args = { arg };
		obj = recibirMensaje(obj, strOp, args);
		if (obj != nullptr)
			return obj;
	}

	pCad = _pCad;
	return nullptr;
}

Object * Parser::unaryMessage() {
	if (debug)
		std::cout << "unaryMessage pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;
	std::string strName;

	//Probamos "receiver name"
	if ((obj = receiver()) != nullptr and name(strName)) {
		std::vector<Object*> args = { };
		obj = recibirMensaje(obj, strName, args);
		if (obj != nullptr)
			return obj;
	}
	pCad = _pCad;

	//Probamos "receiver" (instancia el objeto y lo devuelve)
	if ((obj = receiver()) != nullptr) {
		return obj;
	}

	pCad = _pCad;
	return nullptr;
}

Object * Parser::recibirMensaje(Object* obj, std::string strName,
		std::vector<Object*> &args) {
	if (flagExecute == 1) {
		Object* objMessage = obj->recvMessage(strName, args);
		std::string code = objMessage->getCodeSegment();
		if (code.size() > 0) {
			//El objeto mensaje es un method object
			Parser unParser(vm);
			unParser.setContext(objMessage);
			objMessage->addSlot("self", obj, true, true, false);
			std::vector<Object*> _vector = unParser.run(code);
			obj = _vector[_vector.size() - 1];
			//objMessage->removeSlot("self");
		} else {
			//El objeto mensaje es un data object.
			obj = objMessage;
		}
	}
	// Si no pudo ejecutar el codigo del objeto mensaje devuelve el objeto mensaje.
	//todo verificar si esto esta bien o si se deberia devolver un nilObjk()
	return obj;
}

//2da version del recibirMensaje, se implementara a futuro
//Con la version actual hay un problema con la clonacion de los method objects porque no se detectan correctamente
/*Object * Parser::recibirMensaje2(Object* obj, std::string strName, std::vector<Object*> &args) {
 //std::cout << "recibirMensaje" << std::endl;
 if (flagExecute == 1) {*/
//La asignacion se realiza en el recv_message cuando se le pasa un argumento a un objeto sin argumentos
/* El recv message lo que hace es lo siguiente:
 * Si el objeto strName encontrado es un data object devuelve el mismo objeto.
 * Si es una funcion nativa la ejecuta y retorna el objeto resultado.
 * Si es un method object devuelve el method object con los argumentos pisados (es decir no ejecuto el codigo).

 Lo primero que se debe hacer es verificar si es un data object o un method object.
 * Si es un objeto primitivo ya lo consideramos data object por mas que tenga codeSegment.
 * Ya que la informacion de los objetos primitivos la guardamos en el codeSegment.
 * Si no era objeto primitivo miramos el codeSegment, si tiene codeSegment es un
 * method object, sino es un data object.
 *
 * Si el objeto que recibimos es un data object:
 * le aplicamos al dataObject el recv_message con
 * obj->recvMessage(strName, args);
 * Y luego devolvemos obj.
 * Ejemplo de esto seria cuando hacen: lobby x   (y x = 3.)
 * x es un data object ya que el objeto 3 es primitivo, entonces se devuelve el objeto x.
 *
 * Si el objeto que recibimos es un method object: le aplicamos el recv_message.
 * objMensaje = obj->recvMessage(strName, args);
 * Ahora vamos a tener los atributos seteados
 * Luego ejecutamos el codeSegment.
 Podemos hacerlo analizando el codeSegment (y habria que validar si es un tipo de dato primitivo)
 Hay que crear un atributo en object que indique si es un objeto primitivo.
 Si el objeto que recibimos es un data object (ejemplo lobby)*/

//std::cout << "Cadena:" << cad << std::endl;
//std::cout << "FIN CAD" << std::endl;
//std::cout << "Soy el original" << std::endl;
//obj->printObj(std::vector<Object*>{});
//std::cout << "Soy el clone" << std::endl;
//Object* objClone = obj->clone(std::vector<Object*>{});
//Object* objClone = obj;
//objClone->printObj(std::vector<Object*>{});
//std::cout << "R1" << std::endl;
//Object* objMessage = objClone->recvMessage(strName, args);
//std::cout << "R2" << std::endl;
//context->printObj(std::vector<Object*>{});
//std::string code = objMessage->getCodeSegment();*/
/*std::string code = obj->getCodeSegment();
 if (code.size() > 0) {
 Object* objClone = obj->clone(std::vector<Object*>{});
 Object* objMessage = objClone->recvMessage(strName, args);
 //El objeto mensaje es un method object
 Parser unParser(code);
 unParser.setContext(objMessage);
 objMessage->addSlot("self", obj, true, true, false);
 std::vector<Object*> _vector = unParser.run();
 //objMessage->removeSlot("self");
 obj = _vector[_vector.size() - 1];
 //std::cout << std::endl << "Objeto Recibido de la salida del codesegment: " << std::endl;
 //obj->printObj(std::vector<Object*>{});
 } else {
 //El objeto mensaje es un data object.
 obj = obj->recvMessage(strName, args);
 //std::cout << std::endl << "Objeto Recibido: " << std::endl;
 //obj->printObj(std::vector<Object*>{});
 }
 //obj->printObj(std::vector<Object*>{});
 }
 // Si no pudo ejecutar el codigo del objeto mensaje devuelve el objeto mensaje.
 //todo verificar si esto esta bien o si se deberia devolver un nilObjk()
 //std::cout << std::endl << "Objeto que sale de Recibido: " << std::endl;
 //obj->printObj(std::vector<Object*>{});
 return obj;
 }*/

Object * Parser::receiver() {
	if (debug)
		std::cout << "receiver pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint;
	Object* obj;
	if ((obj = expressionCP()) != nullptr)
		return obj;

	pCad = _pCad;
	return obj;
}

bool Parser::isLowercaseLetter() {
	int _pCad = pCad; //checkpoint;
	char cCad = cad[pCad];
	if ('a' <= cCad and cCad <= 'z') {
		pCad++;
		return true;
	}
	pCad = _pCad;
	return false;
}

bool Parser::isUppercaseLetter() {
	int _pCad = pCad; //checkpoint;
	char cCad = cad[pCad];
	if ('A' <= cCad and cCad <= 'Z') {
		pCad++;
		return true;
	}
	pCad = _pCad;
	return false;
}

bool Parser::isLetter() {
	int _pCad = pCad; //checkpoint;
	if (isLowercaseLetter() or isUppercaseLetter())
		return true;
	pCad = _pCad;
	return false;
}

bool Parser::isSign() {
	int _pCad = pCad; //checkpoint;
	char cCad = cad[pCad];
	if (cCad == '-' or cCad == '+') {
		pCad++;
		return true;
	}
	pCad = _pCad;
	return false;
}

bool Parser::isDigit() {
	int _pCad = pCad; //checkpoint;
	char cCad = cad[pCad];
	if ('0' <= cCad and cCad <= '9') {
		pCad++;
		return true;
	}
	pCad = _pCad;
	return false;
}


bool Parser::isAlpha() {
	int _pCad = pCad; //checkpoint;
	if (isDigit() or isLetter())
		return true;
	pCad = _pCad;
	return false;
}

bool Parser::name(std::string &strName) {
	if (debug)
		std::cout << "name pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();
	strName = "";
	char cCad = cad[pCad];
	if (isLowercaseLetter()) {
		strName += cCad;
		while (pCad < cad.size()) {
			cCad = cad[pCad];
			if (isAlpha())
				strName += cCad;
			else
				break;
		}
	}

	if (strName == "") {
		pCad = _pCad; //checkpoint
		return false;
	} else
		return true;
}

//todo //Asi como esta soporta strings con espacios en medio //No soporta 'hola "'" zaraza' -> falta un detector de doble comilla
std::string Parser::string() {
	if (debug)
		std::cout << "string pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();
	std::string strString = "";
	bool esString = false;
	char cCad = cad[pCad];
	if (isString("'")) {
		strString += cCad;
		while (pCad < cad.size() and !esString) {
			cCad = cad[pCad];
			strString += cCad;
			pCad++;
			if ('\'' == cCad)
				esString = true;
		}
	}

	if (!esString) {
		pCad = _pCad;
		strString = "";
	}
	return strString;
}

//todo //Por ahora solo soporta numeros enteros positivos
bool Parser::number(float &number) {
	if (debug)
		std::cout << "number pos: " << pCad << std::endl;

	skipSpaces();
	std::string strNumber = "";
	char cCad = cad[pCad];
	if (isSign() or isDigit()) {
		strNumber += cCad;
		while (pCad < cad.size()) {
			cCad = cad[pCad];
			if (isDigit())
				strNumber += cCad;
			else
				break;
		}
	}

	if (strNumber != "") {
		number = std::stof(strNumber);
		return true;
	} else
		return false;
}

bool Parser::lowerKeyword(std::string &strLowerKeyword) {
	if (debug)
		std::cout << "lowerKeyword pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();
	strLowerKeyword = "";
	char cCad = cad[pCad];
	if (isLowercaseLetter() or isString("_")) {
		strLowerKeyword += cCad;
		while (pCad < cad.size()) {
			cCad = cad[pCad];
			if (isAlpha())
				strLowerKeyword += cCad;
			else
				break;
		}
	}

	if (strLowerKeyword == "") {
		pCad = _pCad;
		return false;
	} else
		return true;
}

bool Parser::capKeyword(std::string &strCapKeyword) {
	if (debug)
		std::cout << "capKeyword pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();
	strCapKeyword = "";
	char cCad = cad[pCad];
	if (isUppercaseLetter() or isString("_")) {
		strCapKeyword += cCad;
		while (pCad < cad.size()) {
			cCad = cad[pCad];
			if (isAlpha()) {
				strCapKeyword += cCad;
			} else
				break;
		}
	}

	if (strCapKeyword == "") {
		pCad = _pCad;
		return false;
	} else
		return true;
}

Object * Parser::objectObj() {
	if (debug)
		std::cout << "object pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;
	obj = vm.createEmptyObject();
	int inicioScript, finScript;

	if (isString(P_LEFT) and isString(SLOT_LIST_SEP) and slotList(obj)
			and isString(SLOT_LIST_SEP) and (inicioScript = pCad)
			and (script().size() >= 0) and (finScript = pCad)
			and isString(P_RIGHT)) {
		obj->setCodeSegment(cad.substr(inicioScript, finScript - inicioScript));
		return obj;
	} else {
		//todo destruir objeto creado
		pCad = _pCad;
		return nullptr;
	}
	return obj;
}

//todo
bool Parser::slotList(Object* objContenedor) {
	if (debug)
		std::cout << "slotList pos: " << pCad << std::endl;
	//int _pCad = pCad; //checkpoint
	int tipoSlot; //0 normal, 1 argumento, 2 parent
	std::string strName;
	std::string strOpSlot;
	Object* objSlot;

	//todo, quedo medio negro, hay que cambiar las definiciones de tipoSlot
	int pLastSlot = pCad;
	while (pCad < cad.size()) {
		if (slotNameExtended(tipoSlot, strName) and (operadorSlot(strOpSlot))
				and (objSlot = expression()) and isString(PUNTO)) {
			bool esMutable = true;
			bool esParent = false;
			bool esArgument = false;
			if (tipoSlot == 1)
				esArgument = true;
			else if (tipoSlot == 2)
				esParent = true;

			if (strOpSlot == OP_SLOT_INMUTABLE)
				esMutable = false;
			else if (strOpSlot == OP_SLOT_MUTABLE)
				esMutable = true;

			objContenedor->addSlot(strName, objSlot, esMutable, esParent,
					esArgument);
			pLastSlot = pCad;
		} else {
			pCad = pLastSlot;
			if (slotNameExtended(tipoSlot, strName) and isString(PUNTO)) {
				objSlot = vm.createNil(); //todo: si se usa la expression() se pierde esta ref y se likea
				bool esMutable = true;
				bool esParent = false;
				bool esArgument = false;
				if (tipoSlot == 1)
					esArgument = true;
				else if (tipoSlot == 2)
					esParent = true;

				objContenedor->addSlot(strName, objSlot, esMutable, esParent,
						esArgument);
				pLastSlot = pCad;
			} else {
				pCad = pLastSlot;
				break;
			}
		}
	}
	//es equivalente a decir que el slotlist esta vacio
	//por eso se devuelve true, porque es una opcion válida
	//pCad = _pCad;
	return true;
}

bool Parser::slotNameExtended(int &tipoSlot, std::string &strName) {
	if (debug)
		std::cout << "slotNameExtended pos: " << pCad << std::endl;

	skipSpaces();
	int _pCad = pCad; //checkpoint
	if (isString(OP_ARG) and name(strName)) {
		tipoSlot = 1;
	} else {
		pCad = _pCad;
		if (name(strName) and isString(OP_PARENT)) {
			tipoSlot = 2;
		} else {
			pCad = _pCad;
			if (name(strName) or operador(strName)) {
				tipoSlot = 0;
			}
		}
	}
	return true;
}

//todo falta name bool
Object * Parser::constant() {
	if (debug)
		std::cout << "constant pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	Object* obj;

	if ((obj = nilObj()) != nullptr)
		return obj;
	else if ((obj = boolObj()) != nullptr)
		return obj;
	else if ((obj = stringObj()) != nullptr)
		return obj;
	else if ((obj = numberObj()) != nullptr)
		return obj;
	else if ((obj = objectObj()) != nullptr)
		return obj;
	else if ((obj = nameObj(context)) != nullptr)
		return obj;
	else {
		pCad = _pCad;
		return nullptr;
	}
}

bool Parser::operador(std::string &strOperador) {
	if (debug)
		std::cout << "operador pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();

	if (isString(OP_SUMA)) {
		strOperador = OP_SUMA;
		return true;
	} else if (isString(OP_RESTA)) {
		strOperador = OP_RESTA;
		return true;
	} else if (isString(OP_MULTIPLICACION)) {
		strOperador = OP_MULTIPLICACION;
		return true;
	} else if (isString(OP_DIVISION)) {
		strOperador = OP_DIVISION;
		return true;
	} else if (isString(OP_DISTINTO)) {
		strOperador = OP_DISTINTO;
		return true;
	} else if (isString(OP_IGUAL)) {
		strOperador = OP_IGUAL;
		return true;
	} else {
		strOperador = "";
		pCad = _pCad;
		return false;
	}
}

bool Parser::operadorSlot(std::string &strOperadorSlot) {
	if (debug)
		std::cout << "operadorSlot pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();

	if (isString(OP_SLOT_INMUTABLE)) {
		strOperadorSlot = OP_SLOT_INMUTABLE;
		return true;
	} else if (isString(OP_SLOT_MUTABLE)) {
		strOperadorSlot = OP_SLOT_MUTABLE;
		return true;
	} else {
		strOperadorSlot = "";
		pCad = _pCad;
		return false;
	}
}

void Parser::skipSpaces() {
	//if (debug)
	//	std::cout << "skipSpaces pos: " << pCad << std::endl;

	char cCad;
	bool salir = false;
	while (pCad < cad.size() and !salir) {
		cCad = cad[pCad];
		if (cCad == ' ' or cCad == '\t' or cCad == '\n')
			pCad++;
		else
			salir = true;
	}
}

bool Parser::isString(const std::string strMatch) {
	if (debug)
		std::cout << strMatch << " pos: " << pCad << std::endl;

	int _pCad = pCad; //checkpoint
	skipSpaces();
	bool isMatch = true;

	for (uint32_t i = 0; i < strMatch.size(); i++) {
		if ((pCad < cad.size()) and (strMatch[i] == cad[pCad]))
			pCad++;
		else
			isMatch = false;
	}

	if (!isMatch)
		pCad = _pCad;
	return isMatch;
}

Object * Parser::nilObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();

	if (isString(NIL)) {
		obj = vm.createNil();
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object * Parser::boolObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();

	if (isString(TRUE_STR)) {
		obj = vm.createBoolean(true);
		return obj;
	} else if (isString(FALSE_STR)) {
		obj = vm.createBoolean(false);
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object * Parser::stringObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();
	std::string strString = string();

	if (strString != "") {
		obj = vm.createString(strString);
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object * Parser::numberObj() {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();

	float tempNumber = 0;
	if (number(tempNumber)) {
		obj = vm.createNumber(tempNumber);
		return obj;
	}

	pCad = _pCad;
	return obj;
}

Object * Parser::nameObj(Object* &context) {
	int _pCad = pCad; //checkpoint
	Object *obj = nullptr;
	skipSpaces();
	std::string strName;

	if (name(strName)) {
		//std::cout << strName << " es name. pos: " << pCad << std::endl;
		if (flagExecute == 1) {
			std::vector<Object*> args = { };
			obj = recibirMensaje(context, strName, args);
			//obj = context->recvMessage(strName, std::vector<Object*> { });
		} else {
			//Se utiliza cuando no se debe ejecutar el codigo
			//std::cout <<" no ejecutar: " << std::endl;
			obj = vm.createNil();
		}
	} else
		pCad = _pCad;

	return obj;
}

void Parser::setContext(Object* context) {
	this->context = context;
}
