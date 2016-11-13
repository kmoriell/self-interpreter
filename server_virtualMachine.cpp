#include "server_virtualMachine.h"

#include <string> //todo nova
#include <iostream>//todo nova

const std::string NIL = "nil";
const std::string TRUE = "true";
const std::string FALSE = "false";
const std::string PUNTO = ".";

Object* VirtualMachine::createString() {
	//std::cout << "Creando objeto string" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName("string");
	obj->enableNativeMethod(obj, METHOD_PRINT);
	//obj->enableNativeMethod(obj, OP_SUMA);
	//obj->enableNativeMethod(obj, OP_IGUAL);
	//obj->enableNativeMethod(obj, OP_DISTINTO);
	objects.push(obj);

	return obj;
}

Object* VirtualMachine::createNumber() {
	//std::cout << "Creando objeto number" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName("number");
	obj->enableNativeMethod(obj, METHOD_PRINT);
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
	obj->setName("nil");
	obj->setCodeSegment(NIL + PUNTO);
	//obj->enableNativeMethod(obj, OP_IGUAL");
	//obj->enableNativeMethod(obj, OP_DISTINTO);
	objects.push(obj);

	return obj;
}

Object* VirtualMachine::createEmptyObject() {
	//std::cout << "Creando objeto vacio" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName("object");
	//obj->enableNativeMethod(obj, OP_IGUAL");
	//obj->enableNativeMethod(obj, OP_DISTINTO);
	objects.push(obj);

	return obj;
}

Object* VirtualMachine::createBoolean() {
	//std::cout << "Creando objeto booleano" << std::endl; //todo nova
	Object *obj = new Object();
	obj->setName("bool");
	obj->enableNativeMethod(obj, METHOD_PRINT);
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
