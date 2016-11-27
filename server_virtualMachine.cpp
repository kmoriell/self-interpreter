#include "server_virtualMachine.h"

#include <string>
#include <iostream>
#include "common_define.h"

/*const std::string NIL = "nil";
 const std::string TRUE = "true";
 const std::string FALSE = "false";
 const std::string PUNTO = ".";*/

void VirtualMachine::setLobby(Object* lobby) {
    this->lobby = lobby;
}

Object* VirtualMachine::createString(std::string &strString) {
    Object *obj = new Object(lobby);
    obj->setPrimitive(true);
    obj->setName(STRING_OBJ);
    obj->setCodeSegment(strString + PUNTO);
    obj->enableNativeMethod(PRINT_METHOD);
    //obj->enableNativeMethod(obj, OP_SUMA);
    //obj->enableNativeMethod(obj, OP_IGUAL);
    //obj->enableNativeMethod(obj, OP_DISTINTO);
    lobby->addCreatedObject(obj);
    return obj;
}

Object* VirtualMachine::createNumber(float number) {
    Object *obj = new Object(lobby);
    obj->setPrimitive(true);
    obj->setName(NUMBER_OBJ);
    //todo Casteamos a int porque el parser aun no soporta floats
    obj->setCodeSegment(std::to_string((int) number) + PUNTO);
    obj->enableNativeMethod(PRINT_METHOD);
    obj->enableNativeMethod(OP_SUMA);
    obj->enableNativeMethod(OP_RESTA);
    obj->enableNativeMethod(OP_MULTIPLICACION);
    obj->enableNativeMethod(OP_DIVISION);
    //obj->enableNativeMethod(obj, OP_IGUAL");
    //obj->enableNativeMethod(obj, OP_DISTINTO);
    lobby->addCreatedObject(obj);
    return obj;
}

Object* VirtualMachine::createNil() {
    Object *obj = new Object(lobby);
    obj->setPrimitive(true);
    obj->setName(NIL_OBJ);
    obj->setCodeSegment(NIL + PUNTO);
    obj->enableNativeMethod(PRINT_METHOD);
    //obj->enableNativeMethod(obj, OP_IGUAL");
    //obj->enableNativeMethod(obj, OP_DISTINTO);
    lobby->addCreatedObject(obj);
    return obj;
}

Object* VirtualMachine::createEmptyObject() {
    Object *obj = new Object(lobby);
    obj->setName(COMPLEX_OBJ);
    lobby->addCreatedObject(obj);
    return obj;
}

Object* VirtualMachine::createBoolean(bool value) {
    Object *obj = new Object(lobby);
    obj->setPrimitive(true);
    obj->setName(BOOLEAN_OBJ);
    obj->enableNativeMethod(PRINT_METHOD);
    if (value)
        obj->setCodeSegment(TRUE_STR + PUNTO);
    else
        obj->setCodeSegment(FALSE_STR + PUNTO);
    lobby->addCreatedObject(obj);
    return obj;
}

Object* VirtualMachine::findObjectById(uint32_t id) {
    return lobby->findObjectById(id);
}
