/*
 * interpreter.cpp
 *
 *  Created on: 13 de oct. de 2016
 *      Author: kmoriell
 */

#include "interpreter.h"
#include "object.h"
#include <iostream>

void Interpreter::createObject(std::string name) {
  // Tengo la posibilidad de tener objetos sin nombre
  if (name != "") {
    auto it = global_objects.find(name);

    if (it != global_objects.end())
      throw std::runtime_error("Ya existe un objeto con este nombre.");
  }

  Object *newObject = new Object();
  newObject->setName(name);

  global_objects.insert(std::make_pair(name, newObject));
}

void Interpreter::addSlot(std::string object, std::string slot_name, std::vector<std::string> args, bool _mutable,
                          std::vector<opcode_t> code) {
  auto it = global_objects.find(object);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Object *_object = it->second;
  Object *type = nullptr;

  for (auto _code : code) {
    std::string recv = _code.receiver;
    // Verifico que args sea un objeto existente en global_objects
    auto _it = global_objects.find(recv);
    if (_it == global_objects.end()) {
      type = new Object();
      if (::atof(recv.c_str()) || recv == "0" || recv == "0.0" || recv.find('\'') != std::string::npos)
        type->setValue(recv);
      else {
        Object *__slot = new Object();
        type->_AddSlots(recv, __slot, true, false);
      }
    } else {
      type = _it->second;
    }
  }
  if (type == nullptr)
    throw std::runtime_error("type nulo");

  type->setCode(code);

  _object->_AddSlots(slot_name, type, _mutable, false);
}

void Interpreter::call(std::string name, std::string message, std::vector<opcode_t> args) {
  // Si tiene parentesis llamar recursivamente con el contenido del parentesis
  auto it = global_objects.find(name);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Object *object = it->second;
  object->recvMessage(name, message, args);
}
