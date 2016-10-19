#include "object.h"

#include <map>

Object::Object() {
    this->name = "object";
}

Object::Object(const Object& _lobby) {
    this->slots = _lobby.slots;
    this->methods = _lobby.methods;
    this->_mutable = _lobby._mutable;
    this->name = "copy of " + _lobby.name;
}

Object::~Object() {
    slots.clear();
}

void Object::setName(const std::string newName) {
this->name = newName;
}

std::string Object::getName() const {
  return this->name;
}

void Object::setValue(const std::string newValue) {
  this->internal_value = newValue;
}

void Object::_AddSlots(std::string name, Object* obj, bool _mutable, bool isParentSlot) {
    this->slots.insert(std::make_pair(name, std::make_tuple(obj, _mutable, isParentSlot)));
}

void Object::_RemoveSlots (std::string name) {
 auto it = slots.find(name);
    if (it != slots.end()) {
        slots.erase(it);
    } else
        throw std::runtime_error(
        "No existe el slot que se quiere borrar.");
}

Object* Object::clone(const std::vector<Object *> &args) {
    return new Object(*this);
}

std::vector<opcode_t> Object::getCode() const {
  return this->instructions;
}

void Object::setCode(const std::vector<opcode_t> code) {
  this->instructions = code;
}

Object* Object::recvMessage(std::string message, std::vector<std::string> args) {
  // Reviso en los slots del objeto si existe el mensaje
  auto it = slots.find(message);
  if (it == slots.end()) {
    // Entonces busco en los slots del parent slot
    auto parentSlots = getParentSlots();
    for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it)  {
      auto parent = std::get<0>(_it->second);

    }
  } else {
    // Aca tengo mi puntero a objeto, lo que tendria que hacer es ejecutar el codigo
    // del mensaje, tomando
    Object* object = std::get<0>(it->second);
    // Una vez que tengo el objeto, necesito los argumentos, si es que tiene
    // y les cambio el valor con los argumentos que se pasaron como parametro
    auto object_slots = object->getSlots();
    uint32_t i = 0;
    for (auto object_slots_it = object_slots.begin();
        object_slots_it != object_slots.end(); ++object_slots_it) {
      // Verifico que la cant de argumentos sean iguales que los pasados,
      // para ahorrar ciclos.
      if (i == args.size())
        break;

      // Verifico que sea argumento y que el slot sea mutable para poder modificarlo
      if (object_slots_it[0] == ':' && (std::get<1>(object_slots_it))) {
        ((Object*)std::get<0>(object_slots_it))->setValue(args[i]);
        i++;
      }
    }

    for (uint32_t instr = 0; instr < object->instructions; instr++) {

    }

    return object;
  }
}

std::map<std::string, std::tuple<Object*, bool, bool> > getParentSlots() {
  std::map<std::string, std::tuple<Object*, bool, bool> > parentSlots;
  for (auto it = slots.begin(); it != slots.end(); ++it) {
    if (std::get<2>(it->second))
      parentSlots.insert(it);
  }
  return parentSlots;
}
