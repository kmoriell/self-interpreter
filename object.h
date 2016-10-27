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
   * booleano que indica si esta implementado nativamente
   */
  typedef std::tuple<Object*, bool, bool> slot_t;
  typedef std::map<std::string, slot_t> slot_map;
  typedef std::tuple<delegate, bool> fpointTuple;
 private:
  std::string name;
  slot_map slots;
  std::string codeSegment;
  std::map<std::string, fpointTuple> nativeMethods;

  slot_map getParentSlots() const;
  //Object* findObject(std::string name, Object* object);
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
  void _AddSlots(std::string name, Object* obj, bool _mutable,
          bool isParentSlot);
  void _RemoveSlots(std::string name);

  void setCodeSegment(const std::string code);
  std::string getCodeSegment() const;

  Object* recvMessage(Object* object, std::string messageName,
                              std::vector<Object*> args);
  Object* clone(const std::vector<Object*>& args);
  Object* collect();

  // funciones Nativas
  Object* print(const std::vector<Object*>&);
  Object* printObj(const std::vector<Object*>&);
  Object* operator*(const std::vector<Object*>& args);
  Object* operator+(const std::vector<Object*>& args);
  Object* operator-(const std::vector<Object*>& args);
  Object* operator/(const std::vector<Object*>& args);

 // void mostrar();
  void mostrar();

  void enableNativeMethod(Object* object, std::string methodName);
  void disableNativeMethod(Object* object, std::string methodName);
};



#endif /* OBJECT_H_ */
