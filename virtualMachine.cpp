#include "virtualMachine.h"

Object* VirtualMachine::createString(){
  Object *obj = new Object();
  obj->enableNativeMethod(obj, METHOD_PRINT);
  //obj->enableNativeMethod(obj, OP_SUMA);
  //obj->enableNativeMethod(obj, OP_IGUAL);
  //obj->enableNativeMethod(obj, OP_DISTINTO);
  objects.push(obj);

  return obj;
}

Object* VirtualMachine::createNumber(){
  Object *obj = new Object();
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

Object* VirtualMachine::createNil(){
  Object *obj = new Object();
  //obj->enableNativeMethod(obj, OP_IGUAL");
  //obj->enableNativeMethod(obj, OP_DISTINTO);
  objects.push(obj);

  return obj;
}

Object* VirtualMachine::createBoolean(){
  Object *obj = new Object();
  obj->enableNativeMethod(obj, METHOD_PRINT);
  objects.push(obj);

  return obj;
}

VirtualMachine::~VirtualMachine(){

}
