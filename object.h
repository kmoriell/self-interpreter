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

  /* puntero a Object con la referencia al objeto*
   * booleano que indica si es mutable o no
   * booleano que indica si el objeto apuntado es un parent slot
   */
  typedef std::tuple<Object*, bool, bool> slot_t;
  typedef std::map<std::string, slot_t> slot_map;
 private:
  std::string name;
  std::string internal_value;
  slot_map slots;
  std::vector<opcode_t> instructions;

  slot_map getParentSlots() const;
  Object* findObject(std::string name, Object* object);
  //slot_t findSlot(std::string name, slot_map slots);

 public:
  Object();
  ~Object();
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

  Object* recvMessage(std::string objectName, std::string messageName,
                       std::vector<opcode_t> args);
  Object* clone(const std::vector<Object*>& args);
  Object* collect();
};



#endif /* OBJECT_H_ */
