/*
 * interpreter.cpp
 *
 *  Created on: 13 de oct. de 2016
 *      Author: kmoriell
 */

#include "interpreter.h"

#include "object.h"

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

void Interpreter::setObjectAttributes(std::string name, std::map<std::string, Object*> attributes) {
  /*auto it = global_objects.find(name);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Lobby* object = it->second;
  object->setAttributes(attributes);*/
}


void Interpreter::addSlot(std::string object, std::string slot_name, std::vector<std::string> args, bool _mutable,
                          std::vector<opcode_t> code) {
  auto it = global_objects.find(object);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Object *_object = it->second;
  Object *type;

  for (auto arg : args) {
    // Verifico que args sea un objeto existente en global_objects
    auto _it = global_objects.find(arg);
    if (_it == global_objects.end()) {
      type = new Object();
      if (::atof(arg) || arg == "0" || arg == "0.0" || arg.find('\'') != std::string::npos)
        type->setValue(arg);
      else {
        Object *__slot = new Object();
        type->_AddSlots(arg, __slot, true, false);
      }
    } else {
      type = _it->second;
    }
  }

  type->setCode(code);
}

void Interpreter::call(std::string name, std::string method, std::vector<Object*> params) {
  // Si tiene parentesis llamar recursivamente con el contenido del parentesis
  auto it = global_objects.find(name);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Object *object = it->second;
  object->recvMessage(method, params);
}

Object* Interpreter::process(Object* object) {

  std::vector<opcode_t> instructions = currentSlot.instructions;
  //Lobby* _object = object;
  for (uint32_t i = 0; i < instructions.size(); i++) {
    opcode_t current_opcode = instructions[i];

    process_internal(current_opcode, currentSlot, object);
  }
  return object;
}

Object* Interpreter::process_internal(opcode_t __opcode, slot_t currentSlot, Object* object) {

  Object* operand1;

  // Busco el primer y segundo operando en el slot actual, si no lo encuentro
  // voy al slot principal, si no emito un error
  operand1 = getOperand(__opcode.operands[0], currentSlot, object);
  std::vector<Object*> vec;
  for (uint32_t i = 1; i < __opcode.operands.size(); i++) {
    vec.push_back(getOperand(__opcode.operands[i], currentSlot, object));
  }

  // Busco en los slots del operando la instuccion que quiero ejecutar
  slot_t _slot = operand1->getSlot(__opcode.operands[0]);

  /*if (_slot.arguments.size() != (__opcode.operands.size() - 1)) {
    throw "excepcion";
  }

  int arg = 1;
  for (auto i : _slot.arguments) {
    Lobby* operand2 = getOperand(__opcode.operands[arg], currentSlot, object);
    i = operand2;
    arg++;
  }*/
  //_slot.arguments.find()

  // Mandar el mensaje _slot a operand1
  // La idea es ya que tengo un diccionario con el nombre y punteros a Lobby,
  // busco el nombre en los metodos y tengo el puntero a la funcion que lo hace.
  // Si devuelve nullptr, llamo recursivamente sobre la lista de instrucciones
  // hasta resolver la consulta.
  Object::delegate method = operand1->getMethod(__opcode.method);
  if (method == nullptr) {
    return nullptr; //this->process(_slot, operand1);
  } else {
    Object* ret = (operand1->*method)(vec);
    return ret;
    }
}

Object* Interpreter::getOperand(std::string instr, slot_t currentSlot, Object* object) {
  auto it = currentSlot.arguments.find(instr);
  if (it == currentSlot.arguments.end()) {
    // No lo encontre en los argumentos, busco en las variables locales
    auto _local_vars_it = currentSlot.localVariables.find(instr);
    if (_local_vars_it == currentSlot.localVariables.end()) {
      // No esta en las variables locales, busco en el slot principal
      // TODO: optimizar, llamar al slot que contiene a este slot. Hacer recursivo
      // hasta llegar al principal.
      try {
        slot_t _main_slot = object->getSlot(instr);
        return (Object*)_main_slot.localVariables.find(instr)->second;
      } catch(const std::runtime_error &e) {
        std::string error1 = "No existe el slot ";
        error1 += instr;
        throw std::runtime_error(error1);
      }
    } else {
      return (Object*)_local_vars_it->second;
    }
  }

  return (Object*)it->second;
}

