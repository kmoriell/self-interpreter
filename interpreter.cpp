/*
 * interpreter.cpp
 *
 *  Created on: 13 de oct. de 2016
 *      Author: kmoriell
 */

#include "interpreter.h"
#include "lobby.h"

void Interpreter::createObject(std::string name) {
  // Tengo la posibilidad de tener objetos sin nombre
  if (name != "") {
    auto it = global_objects.find(name);

    if (it != global_objects.end())
      throw std::runtime_error("Ya existe un objeto con este nombre.");
  }

  Lobby *newObject = new Lobby();
  newObject->setName(name);

  global_objects.insert(std::make_pair(name, newObject));
}

void Interpreter::setObjectAttributes(std::string name, std::map<std::string, Lobby*> attributes) {
  /*auto it = global_objects.find(name);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Lobby* object = it->second;
  object->setAttributes(attributes);*/
}

void Interpreter::addSlot(std::string object, std::string slot_name, slot_t newSlot) {
  auto it = global_objects.find(object);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Lobby *_object = it->second;

  //
  Lobby *type;

  // Verifico que el slot tenga una operacion de "=" o "<-".
  for (auto i : newSlot.instructions) {
    std::string operation = i.method;
    std::string operand1 = i.operands[0];
     if (operation == "print") {
    if (operand1.find('\'') != std::string::npos ||
                operand1.find('"') != std::string::npos) {
        std::string newString = operand1.substr(1, operand1.size() - 2);
        type = new String(newString);
        slot_t _type_slot = newSlot;
        /*opcode_t assignation;
        assignation.method = "=";
        assignation.operands = std::vector<std::string>{operand1};*/
        newSlot.localVariables.insert(std::make_pair(operand1, type));
        //std::vector<opcode_t> _newSlot_instructions = newSlot.instructions;
        //newSlot.instructions = std::vector<opcode_t> { assignation };
        /*for ( auto i : _newSlot_instructions)
            newSlot.instructions.push_back(i);*/

        type->_AddSlots(operand1, newSlot);
    }
  }
  else if (operation == "=" || operation == "<-") {
    std::string operand2 = i.operands[1];
    if (::atof(operand2.c_str()) || (operand2 == "0" || operand2 == "0.0")) {
        type = new Number(::atof(operand2.c_str()));
        //slot_t _type_slot = newSlot;
        newSlot.localVariables.insert(std::make_pair(slot_name, type));
        type->_AddSlots(operand1, newSlot);
    } else if (operand2.find('\'') != std::string::npos ||
                operand2.find('"') != std::string::npos) {
        type = new String();
        slot_t _type_slot = newSlot;
        _type_slot.localVariables.insert(std::make_pair(slot_name, type));
        type->_AddSlots(operand1, _type_slot);
    } else {
        type = new Lobby();
    }
    newSlot.localVariables.insert(std::make_pair(slot_name, type));
  }
  }
  _object->_AddSlots(slot_name, newSlot);
  it->second = _object;
}

void Interpreter::call(std::string name, std::string method, std::vector<Lobby*> params) {
  // Si tiene parentesis llamar recursivamente con el contenido del parentesis
  auto it = global_objects.find(name);

  if (it == global_objects.end())
    throw std::runtime_error("El objeto no existe.");

  Lobby *object = it->second;
  slot_t current_slot = object->getSlot(method);


  process(current_slot, object);
}

Lobby* Interpreter::process(slot_t currentSlot, Lobby* object) {
  std::vector<opcode_t> instructions = currentSlot.instructions;
  //Lobby* _object = object;
  for (uint32_t i = 0; i < instructions.size(); i++) {
    opcode_t current_opcode = instructions[i];

    process_internal(current_opcode, currentSlot, object);
  }
  return object;
}

Lobby* Interpreter::process_internal(opcode_t __opcode, slot_t currentSlot, Lobby* object) {

  Lobby* operand1;

  // Busco el primer y segundo operando en el slot actual, si no lo encuentro
  // voy al slot principal, si no emito un error
  operand1 = getOperand(__opcode.operands[0], currentSlot, object);
  std::vector<Lobby*> vec;
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
  Lobby::delegate method = operand1->getMethod(__opcode.method);
  if (method == nullptr) {
    return nullptr; //this->process(_slot, operand1);
  } else {
    Lobby* ret = (operand1->*method)(vec);
    return ret;
    }
}

Lobby* Interpreter::getOperand(std::string instr, slot_t currentSlot, Lobby* object) {
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
        return (Lobby*)_main_slot.localVariables.find(instr)->second;
      } catch(const std::runtime_error &e) {
        std::string error1 = "No existe el slot ";
        error1 += instr;
        throw std::runtime_error(error1);
      }
    } else {
      return (Lobby*)_local_vars_it->second;
    }
  }

  return (Lobby*)it->second;
}

