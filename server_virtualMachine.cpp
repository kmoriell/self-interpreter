#include "server_virtualMachine.h"

#include <string>
#include <iostream>
#include "common_define.h"

/*const std::string NIL = "nil";
 const std::string TRUE = "true";
 const std::string FALSE = "false";
 const std::string PUNTO = ".";*/

Object* VirtualMachine::createString(std::string &strString) {
	//std::cout << "Creando objeto string" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName(STRING_OBJ);
	obj->setCodeSegment(strString + PUNTO);
	obj->enableNativeMethod(obj, PRINT_METHOD);
	//obj->enableNativeMethod(obj, OP_SUMA);
	//obj->enableNativeMethod(obj, OP_IGUAL);
	//obj->enableNativeMethod(obj, OP_DISTINTO);
	objects.push(obj);

	return obj;
}

Object* VirtualMachine::createNumber(float number) {
	//std::cout << "Creando objeto number" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName(NUMBER_OBJ);
	//todo Casteamos a int porque el parser aun no soporta floats
	obj->setCodeSegment(std::to_string((int) number) + PUNTO);
	obj->enableNativeMethod(obj, PRINT_METHOD);
	obj->enableNativeMethod(obj, OP_SUMA);
	obj->enableNativeMethod(obj, OP_RESTA);
	obj->enableNativeMethod(obj, OP_MULTIPLICACION);
	obj->enableNativeMethod(obj, OP_DIVISION);
	//obj->enableNativeMethod(obj, OP_IGUAL");
	//obj->enableNativeMethod(obj, OP_DISTINTO);
	objects.push(obj);

	return obj;
}

Object* VirtualMachine::createNil() {
	//std::cout << "Creando objeto nil" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName(NIL_OBJ);
	obj->setCodeSegment(NIL + PUNTO);
	obj->enableNativeMethod(obj, PRINT_METHOD);
	//obj->enableNativeMethod(obj, OP_IGUAL");
	//obj->enableNativeMethod(obj, OP_DISTINTO);
	objects.push(obj);

	return obj;
}

Object* VirtualMachine::createEmptyObject() {
	//std::cout << "Creando objeto vacio" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName(COMPLEX_OBJ);
	objects.push(obj);

	return obj;
}

Object* VirtualMachine::createBoolean(bool value) {
	//std::cout << "Creando objeto booleano" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName(BOOLEAN_OBJ);
	obj->enableNativeMethod(obj, PRINT_METHOD);
	if (value)
		obj->setCodeSegment(TRUE + PUNTO);
	else
		obj->setCodeSegment(FALSE + PUNTO);
	objects.push(obj);

	return obj;
}

VirtualMachine::~VirtualMachine() {
	while (objects.size() > 0) {
		Object *obj = objects.top();
		delete obj;

		objects.pop();
	}
}
