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

  for (uint32_t i = 0; i < instructions.size(); i++) {
    opcode_t current_opcode = instructions[i];
  }
}

Lobby* Interpreter::process_internal(opcode_t __opcode, slot_t currentSlot, Lobby* object) {

  Lobby* operand1;

  // Busco el primer y segundo operando en el slot actual, si no lo encuentro
  // voy al slot principal, si no emito un error
  operand1 = getOperand(__opcode.operands[0], currentSlot, object);
  Lobby* operand2 = getOperand(__opcode.operands[2], currentSlot, object);

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
    return this->process(_slot, operand1);
  } else {
    // TODO: mi problema lo tengo aca, porque no puedo llamar a la funcion
    // apuntada por method.
    std::vector<Lobby*> vec;
    vec.push_back(operand2);
    //delegate = method;
    Lobby* ret = (method)(vec);
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
        throw std::runtime_error("No existe el slot");
      }
    } else {
      return (Lobby*)_local_vars_it->second;
    }
  }

  return (Lobby*)it->second;
}

