/*
 * lobby.h
 *
 *  Created on: 14 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include <stdexcept>
#include <map>
#include <tuple>
#include "opcodes.h"

class Object {
public:
  typedef Object* (Object::*delegate)(const std::vector<Object*>&);
 private:
  std::string name;
  std::string internal_value;
  // {nombre, (Object*, mutable?, parentSlot?
  std::map<std::string, std::tuple<Object*, bool, bool> > slots;
  std::vector<opcode_t> instructions;
  std::map<std::string, std::tuple<Object*, bool, bool> > getParentSlots();

  std::map<std::string, std::tuple<Object*, bool, bool> > getSlots() const;

 public:
  Object();
  // Constructor copia
  Object(const Object& _lobby);
  void setName(const std::string newName);
  std::string getName() const;
  void _AddSlots(std::string name, Object* obj, bool _mutable, bool isParentSlot);
  void _RemoveSlots(std::string name);

  void setValue(const std::string newValue);
  std::string getValue() const;

  void setCode(const std::vector<opcode_t> code);
  std::vector<opcode_t> getCode() const;

  Object* recvMessage(std::string message, std::vector<std::string> args);
  Object* clone(const std::vector<Object*>& args);
  Object* collect();
};



#endif /* OBJECT_H_ */
