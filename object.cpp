#include "object.h"

#include <map>
#include <iostream>

Object::Object() {
  this->name = "object";
}

Object::Object(const Object& _lobby) {
  /*  this->slots = _lobby.slots;
   this->methods = _lobby.methods;
   this->_mutable = _lobby._mutable;
   this->name = "copy of " + _lobby.name;*/
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

void Object::_AddSlots(std::string name, Object* obj, bool _mutable,
                       bool isParentSlot) {
  this->slots.insert(
      std::make_pair(name, std::make_tuple(obj, _mutable, isParentSlot)));
}

void Object::_RemoveSlots(std::string name) {
  auto it = slots.find(name);
  if (it != slots.end()) {
    slots.erase(it);
  } else
    throw std::runtime_error("No existe el slot que se quiere borrar.");
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

Object* Object::findObject(std::string name, Object* object) {
  if (name == object->name)
    return object;

  slot_map slots = object->slots;
  auto it = slots.find(name);
  if (it == slots.end()) {
    // Entonces busco en los slots del parent slot
    slot_map parentSlots = getParentSlots();
    std::vector<Object*> parentsFound;

    for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
      Object *_temp = (Object*) std::get < 0 > (_it->second);
      Object *parent = findObject(name, _temp);
      parentsFound.push_back(parent);
    }

    // Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
    if (parentsFound.size() != 1) {
      std::string error = "Objeto ";
      error += name + " no encontrado.";
      throw std::runtime_error(error);
    }
    return parentsFound[0];
  } else {
    return (Object*) std::get < 0 > (it->second);
  }
}

/*slot_t Object::findSlot(std::string name, slot_map slots) {
 auto it = slots.find(name);
 if (it == slots.end()) {
 // Entonces busco en los slots del parent slot
 slot_map parentSlots = getParentSlots();
 std::vector<slot_t> parentsFound;

 for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
 slot_t parent = findSlot(name, _it->second);
 parentsFound.push_back(parent);
 }

 // Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
 if (parentsFound.size() != 1) {
 std::string error = "Slot ";
 error += this->name + " no encontrado.";
 throw std::runtime_error(error);
 }
 return parentsFound[0];
 } else {
 return it->second;
 }
 }*/

Object* Object::recvMessage(std::string objectName, std::string messageName,
                            std::vector<opcode_t> args) {
  Object* object = findObject(objectName, this);

  if (messageName == "")
    return object;

  return recvMessage(object, messageName, args);
}

Object* Object::recvMessage(Object* object, std::string messageName,
                            std::vector<opcode_t> args) {
  /*// Reviso en los slots del objeto si existe el mensaje
   auto it = object->slots.find(message);
   if (it == object->slots.end()) {
   // Entonces busco en los slots del parent slot
   auto parentSlots = getParentSlots();
   std::vector<Object*> parentsFound;

   for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
   Object *parent = std::get < 0 > (_it->second);
   parentsFound.push_back(parent);
   }

   // Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
   if (parentsFound.size() != 1) {
   std::string error = message;
   error += " no reconocido por " + this->name;
   throw std::runtime_error(error);
   }
   return recvMessage(parentsFound[0], message, args);

   } else {*/

  // Aca tengo mi puntero a objeto, lo que tendria que hacer es ejecutar el codigo
  // del mensaje
  //Object* foundObject = std::get < 0 > (it->second);
  if (messageName == "")
    return object;

  if (messageName == "print") {
    std::cout << object->internal_value;
    return object;
  } else if (messageName == "+") {
    std::vector<opcode_t> _arguments;
    for (auto _arg : args[0].args)
      _arguments.push_back(*_arg);

    Object* _operand = this->recvMessage(args[0].receiver, args[0].message,
                                         _arguments);
    std::string _operandValue = _operand->internal_value;
    float _operandValuef = ::atof(_operandValue.c_str());
    float internalValuef = ::atof(object->internal_value.c_str());
    Object* _returnValue = new Object;

    if (_operandValuef || _operandValue == "0" || _operandValue == "0.0")
      if (internalValuef || object->internal_value == "0" || object->internal_value == "0.0") {
        float _value_ = _operandValuef + internalValuef;
        _returnValue->internal_value = std::to_string(_value_);
        return _returnValue;
      }
      else {
        delete _returnValue;
        throw std::runtime_error("Mensaje + desconocido");
      }
    else {
      delete _returnValue;
      throw std::runtime_error("Mensaje + desconocido");
    }
  } else if (messageName == "-") {
  } else if (messageName == "*") {
    std::vector<opcode_t> _arguments;
    for (auto _arg : args[0].args)
      _arguments.push_back(*_arg);

    Object* _operand = this->recvMessage(args[0].receiver, args[0].message,
                                         _arguments);
    std::string _operandValue = _operand->internal_value;
    float _operandValuef = ::atof(_operandValue.c_str());
    float internalValuef = ::atof(object->internal_value.c_str());
    Object* _returnValue = new Object;

    if (_operandValuef || _operandValue == "0" || _operandValue == "0.0")
      if (internalValuef || object->internal_value == "0" || object->internal_value == "0.0") {
        float _value_ = _operandValuef * internalValuef;
        _returnValue->internal_value = std::to_string(_value_);
        return _returnValue;
      }
      else {
        delete _returnValue;
        throw std::runtime_error("Mensaje * desconocido");
      }
    else {
      delete _returnValue;
      throw std::runtime_error("Mensaje * desconocido");
    }

  } else if (messageName == "/") {
  }

  Object* message = findObject(messageName, object);
  //slot_t message = findSlot(messageName, object->slots);

  // Una vez que tengo el objeto, necesito los argumentos, si es que tiene
  // y les cambio el valor con los argumentos que se pasaron como parametro
  slot_map object_slots = message->slots;
  uint32_t i = 0;
  for (auto object_slots_it = object_slots.begin();
      object_slots_it != object_slots.end(); ++object_slots_it) {
    // Verifico que la cant de argumentos sean iguales que los pasados,
    // para ahorrar ciclos.
    if (i == args.size())
      break;

    // Verifico que sea argumento y que el slot sea mutable para poder modificarlo
    bool __isMutable = std::get < 1 > (object_slots_it->second);
    std::string slotName = object_slots_it->first;
    if (slotName[0] == ':' && __isMutable) {
      std::string argValueToCopy = args[i].message;
      ((Object*) std::get < 0 > (object_slots_it->second))->setValue(
          argValueToCopy);
      i++;
    }
  }

  Object *result;
  // Ejecuto las instrucciones de codigo que tiene el slot devuelto
  for (auto instr : message->instructions) {
    std::string recv = instr.receiver;
    Object *receiver;

    if (::atof(recv.c_str()) || recv == "0" || recv == "0.0"
        || recv.find('\'') != std::string::npos) {
      auto object_slots_it = this->slots.find(messageName);

      bool __isMutable = std::get < 1 > (object_slots_it->second);
      std::string slotName = object_slots_it->first;
      if (__isMutable) {
        auto actual_value = object_slots_it->second;
        ((Object*) std::get < 0 > (actual_value))->setValue(recv);
        result = (Object*) std::get < 0 > (actual_value);
        object_slots_it->second = actual_value;
      }

    } else {
      if (instr.receiver == "")
        receiver = result;
      else
        receiver = findObject(instr.receiver, this);

      std::vector<opcode_t> _arguments;
      for (auto _arg : instr.args)
        _arguments.push_back(*_arg);

      result = this->recvMessage(receiver, instr.message, _arguments);
    }
  }

  for (auto arg : args) {
    Object *receiver;
    if (arg.receiver == "") {
      receiver = result;
    } else {
      // Poner rutina que me devuelva el objeto
      receiver = findObject(arg.receiver, this);
    }
    std::vector<opcode_t> _arguments;
    for (auto _arg : arg.args)
      _arguments.push_back(*_arg);

    result = this->recvMessage(receiver, arg.message, _arguments);
  }

  if (args.size() > 0)
    message = result;

  return message;
}

std::map<std::string, std::tuple<Object*, bool, bool> > Object::getParentSlots() const {
  std::map<std::string, std::tuple<Object*, bool, bool> > parentSlots;
  for (auto it = slots.begin(); it != slots.end(); ++it) {
    if (std::get < 2 > (it->second))
      parentSlots.insert(std::make_pair(it->first, it->second));
  }
  return parentSlots;
}

std::string Object::getValue() const {
  return this->internal_value;
}
