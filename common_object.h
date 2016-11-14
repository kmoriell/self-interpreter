#ifndef COMMON_OBJECT_H_
#define COMMON_OBJECT_H_

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
   * booleano que indica si es un argumento (:)
   */
  typedef std::tuple<Object*, bool, bool, bool> slot_t;
  typedef std::map<std::string, slot_t> slot_map;
  typedef std::tuple<delegate, bool> fpointTuple;
 private:
  slot_map slots;
  std::string name;
  std::string codeSegment;
  std::map<std::string, fpointTuple> nativeMethods;

  slot_map getParentSlots() const;
  Object::slot_map getParentSlots(Object* pointer) const;
  bool findObject(std::string name, Object* &returnValue,
  		delegate& function);

  /*Object* recvMessage(Object* object, std::string messageName,
                              std::vector<opcode_t> args);*/
  //slot_t findSlot(std::string name, slot_map slots);

 public:
  Object();
  ~Object();
  // Constructor copia
  Object(const Object& __object);
  slot_map getSlots() const;
  Object* _AddSlots(const std::vector<Object*>& args);
  Object* addSlot(std::string name, Object* obj, bool _mutable,	bool isParentSlot, bool isArgument);

  Object* _RemoveSlots(const std::vector<Object*>& args);
  Object* removeSlot(std::string name);

  void setCodeSegment(const std::string code);
  std::string getCodeSegment() const;

  void setName(const std::string name);
  std::string getName() const;

  Object* recvMessage(std::string messageName,
                              std::vector<Object*> args);
  Object* clone(const std::vector<Object*>& args);
  Object* collect();

  // funciones Nativas
  Object* print(const std::vector<Object*>& args);
  Object* printObj(const std::vector<Object*>& args);
  Object* operator*(const std::vector<Object*>& args);
  Object* operator+(const std::vector<Object*>& args);
  Object* operator-(const std::vector<Object*>& args);
  Object* operator/(const std::vector<Object*>& args);

  void enableNativeMethod(Object* object, std::string methodName);
  void disableNativeMethod(Object* object, std::string methodName);
};



#endif /* COMMON_OBJECT_H_ */
