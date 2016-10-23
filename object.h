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
#include <vector>

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
  slot_map slots;
  std::string codeSegment;

  slot_map getParentSlots() const;
  Object* findObject(std::string name, Object* object);
  /*Object* recvMessage(Object* object, std::string messageName,
                              std::vector<opcode_t> args);*/
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

  void setCodeSegment(const std::string code);
  std::string getCodeSegment() const;

  Object* recvMessage(Object* object, std::string messageName,
                              std::vector<Object*> args);
  Object* clone(const std::vector<Object*>& args);
  Object* collect();
};



#endif /* OBJECT_H_ */
